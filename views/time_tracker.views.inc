<?php
// $Id$
/**
 * @file
 *   Views integration for time_tracker
 */

/**
 * Implements hook_views_data().
 */
function time_tracker_views_data() {
  $data['time_tracker_entry']['table']['group'] = t('Time Tracker');

  $data['time_tracker_entry']['table']['base'] = array(
    'field' => 'teid',
    'title' => t('Time Tracker'),
    'help' => t('Content generated from time tracker entries.'),
  );

  $data['time_tracker_entry']['teid'] = array(
    'title' => t('ID'),
    'help' => t('Time Entry ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument',
    ),
  );

  $data['time_tracker_entry']['timestamp'] = array(
    'title' => t('Timestamp'),
    'help' => t('Timestamp of the Entry.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  $data['time_tracker_entry']['duration'] = array(
    'title' => t('Duration'),
    'help' => t('Time Entry Duration.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument',
    ),
  );

  $data['time_tracker_entry']['activity'] = array(
    'title' => t('Activity'),
    'help' => t('Time Entry Activity.'),
    'field' => array(
      'handler' => 'views_handler_field_markup',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['time_tracker_entry']['billable'] = array(
    'title' => t('Billable'),
    'help' => t('Is the Entry Billable?'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument',
    ),
  );

  $data['time_tracker_entry']['uid'] = array(
    'title' => t('Author'),
    'help' => t('Relate an entry to the user who created it.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'base field' => 'uid',
      'label' => t('User'),
    ),
  );

  $data['time_tracker_entry']['nid'] = array(
    'title' => t('Node'),
    'help' => t('Relate an entry to a comments node.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'node',
      'base field' => 'nid',
      'label' => t('Node'),
    ),
  );

  $data['time_tracker_entry']['cid'] = array(
    'title' => t('Comment'),
    'help' => t('Relate an entry to a comment.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'comments',
      'base field' => 'cid',
      'label' => t('Comment'),
    ),
  );

  return $data;
}