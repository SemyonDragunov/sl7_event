<?php

class sl7_event_handler_sl7_event_reg_participant extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['eid'] = 'eid';
    $this->additional_fields['participant'] = array(
      'field' => 'sl7_event_participants_target_id',
      'table' => 'field_data_sl7_event_participants',
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $eid = $this->get_value($values, 'eid');
    $uid = $this->get_value($values, 'participant');

    $flag = flag_get_flag('sl7_event_reg_participant');

    return $flag->theme($flag->is_flagged($eid, $uid) ? 'unflag' : 'flag', $eid, array('uid' => $uid));
  }
}