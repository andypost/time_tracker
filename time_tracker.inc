<?php

/**
 * @file
 * Implements the basic functionality required to create and display an entity.
 *
 */

/**
 * EntityExampleBasicControllerInterface definition.
 *
 * We create an interface here because anyone could come along and
 * use hook_entity_info_alter() to change our controller class.
 * We want to let them know what methods our class needs in order
 * to function with the rest of the module, so here's a handy list.
 *
 * @see hook_entity_info_alter()
 */

interface TimeTrackerControllerInterface
  extends DrupalEntityControllerInterface {
  public function create();
  public function save($entity);
  public function delete($entity);
}

/**
 * EntityExampleBasicController extends DrupalDefaultEntityController.
 *
 * Our subclass of DrupalDefaultEntityController lets us add a few
 * important create, update, and delete methods.
 */
class TimeTrackerController
  extends DrupalDefaultEntityController
  implements TimeTrackerControllerInterface {

  /**
   * Create and return a new time_tracker_entry entity.
   */
  public function create() {
    $entity = new stdClass();
    $entity->type = 'time_tracker_entry';

    $entity->bundle_type = 'time_entry';
    $entity->item_description = '';
    return $entity;
  }

  /**
   * Saves the custom fields using drupal_write_record()
   */
  public function save($entity) {

    // If our entity has no basic_id, then we need to give it a
    // time of creation.
    //if (empty($entity->basic_id)) {
    //  $entity->created = time();
    //}
    // Invoke hook_entity_presave().
    // module_invoke_all('entity_presave', 'time_tracker_entry', $entity);
    // The 'primary_keys' argument determines whether this will be an insert
    // or an update. So if the entity already has an ID, we'll specify
    // basic_id as the key.
//primary_keys = $entity->teid ? 'teid' : array();
    // Write out the entity record.

    drupal_write_record('time_tracker_entry', $entity);
    // We're going to invoke either hook_entity_update() or
    // hook_entity_insert(), depending on whether or not this is a
    // new entity. We'll just store the name of hook_entity_insert()
    // and change it if we need to.
    $invocation = 'entity_insert';
    // Now we need to either insert or update the fields which are
    // attached to this entity. We use the same primary_keys logic
    // to determine whether to update or insert, and which hook we
    // need to invoke.
    if (empty($primary_keys)) {
      field_attach_insert('time_tracker_entry', $entity);
    }
    else {
      field_attach_update('time_tracker_entry', $entity);
      $invocation = 'entity_update';
    }
    // Invoke either hook_entity_update() or hook_entity_insert().
    // module_invoke_all($invocation, 'time_tracker_entry', $entity);
    return $entity;
  }

  /**
   * Delete a single entity.
   *
   * Really a convenience function for delete_multiple().
   */
  public function delete($entity) {
    $this->delete_multiple(array($entity));
  }

  /**
   * Delete one or more time_tracker_entry entities.
   *
   * Deletion is unfortunately not supported in the base
   * DrupalDefaultEntityController class.
   *
   * @param $basic_ids
   *   An array of entity IDs or a single numeric ID.
   */
  public function delete_multiple($entities) {
    $basic_ids = array();
    if (!empty($entities)) {
      $transaction = db_transaction();
      try {
        foreach ($entities as $entity) {
          module_invoke_all('time_tracker_entry_delete', $entity);
          // Invoke hook_entity_delete().
          module_invoke_all('entity_delete', $entity, 'time_tracker_entry');
          field_attach_delete('time_tracker_entry', $entity);
          $basic_ids[] = $entity->basic_id;
        }
        db_delete('time_tracker_entry')
          ->condition('teid', $basic_ids, '=')
          ->execute();

      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('time_tracker', $e);
        throw $e;
      }
    }
  }
}





