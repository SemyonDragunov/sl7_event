<?php

class sl7_event_handler_operations extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['eid'] = 'eid';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $eid = $this->get_value($values, 'eid');
    $links = array();

    if (sl7_event_access('manage')) {
      $links['edit'] = array(
        'title' => t('Edit'),
        'href'  => SL7_EVENT_PATH . '/' . $eid . '/edit',
        'html'  => FALSE,
      );
      $links['edit']['query'] = drupal_get_destination();
    }

    if (sl7_event_access('mark')) {
      $links['participants'] = array(
        'title' => 'Участники',
        'href'  => SL7_EVENT_PATH . '/' . $eid . '/participants',
        'html'  => FALSE,
      );
      $links['edit']['query'] = drupal_get_destination();
    }

    if (sl7_event_access('delete')) {
      $links['delete'] = array(
        'title' => t('Delete'),
        'href'  => SL7_EVENT_PATH . '/' . $eid . '/delete',
        'html'  => FALSE,
      );
      $links['delete']['query'] = drupal_get_destination();
    }

    return theme('links__ctools_dropbutton', array(
      'links' => $links,
      'attributes' => array(
        'class' => array('links', 'inline', 'operations')
      )
    ));
  }
}