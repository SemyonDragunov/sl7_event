<?php

$view = new view();
$view->name = 'sl7_event';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'sl7_event';
$view->human_name = 'Мероприятия';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Мероприятия';
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['use_more_text'] = 'ещё';
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['exposed_form']['options']['submit_button'] = 'Применить';
$handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
$handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Сбросить';
$handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Сортировать по';
$handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'По возрастанию';
$handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'По убыванию';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '30';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Элементов на страницу';
$handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
$handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Все -';
$handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Пропустить';
$handler->display->display_options['pager']['options']['tags']['first'] = '« первая';
$handler->display->display_options['pager']['options']['tags']['previous'] = '‹ предыдущая';
$handler->display->display_options['pager']['options']['tags']['next'] = 'следующая ›';
$handler->display->display_options['pager']['options']['tags']['last'] = 'последняя »';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'eid' => 'eid',
  'label' => 'label',
  'sl7_event_date' => 'sl7_event_date',
  'uid' => 'uid',
  'seats' => 'seats',
  'free' => 'free',
  'amount' => 'amount',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'eid' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'label' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'sl7_event_date' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'uid' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'seats' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'free' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'amount' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* Поле: Мероприятие: Идентификатор Мероприятие */
$handler->display->display_options['fields']['eid']['id'] = 'eid';
$handler->display->display_options['fields']['eid']['table'] = 'sl7_event';
$handler->display->display_options['fields']['eid']['field'] = 'eid';
$handler->display->display_options['fields']['eid']['label'] = 'ID';
$handler->display->display_options['fields']['eid']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['eid']['alter']['path'] = 'event/[eid]';
$handler->display->display_options['fields']['eid']['separator'] = '';

/* Display: Список мероприятий */
$handler = $view->new_display('page', 'Список мероприятий', 'main_page');
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'sl7_event participation';
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '15';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Элементов на страницу';
$handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
$handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Все -';
$handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Пропустить';
$handler->display->display_options['pager']['options']['tags']['first'] = '« первая';
$handler->display->display_options['pager']['options']['tags']['previous'] = '‹ предыдущая';
$handler->display->display_options['pager']['options']['tags']['next'] = 'следующая ›';
$handler->display->display_options['pager']['options']['tags']['last'] = 'последняя »';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['style_options']['default_row_class'] = FALSE;
$handler->display->display_options['style_options']['row_class_special'] = FALSE;
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'entity';
$handler->display->display_options['row_options']['view_mode'] = 'teaser';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['header'] = FALSE;
/* Верхний колонтитул: Глобальный: Область представления */
$handler->display->display_options['header']['view']['id'] = 'view';
$handler->display->display_options['header']['view']['table'] = 'views';
$handler->display->display_options['header']['view']['field'] = 'view';
$handler->display->display_options['header']['view']['label'] = 'Календарь';
$handler->display->display_options['header']['view']['view_to_insert'] = 'sl7_event_calendar:mount';
$handler->display->display_options['defaults']['empty'] = FALSE;
/* Поведение при отсутствии результатов: Глобальный: Текстовая область */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['label'] = 'Нет мероприятий';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = 'Нет мероприятий.';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Критерий сортировки: Мероприятие: Дата проведения -  дата начала (sl7_event_date) */
$handler->display->display_options['sorts']['sl7_event_date_value']['id'] = 'sl7_event_date_value';
$handler->display->display_options['sorts']['sl7_event_date_value']['table'] = 'field_data_sl7_event_date';
$handler->display->display_options['sorts']['sl7_event_date_value']['field'] = 'sl7_event_date_value';
$handler->display->display_options['sorts']['sl7_event_date_value']['order'] = 'DESC';
$handler->display->display_options['path'] = 'event';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Мероприятия';
$handler->display->display_options['menu']['weight'] = '1';
$handler->display->display_options['menu']['name'] = 'main-menu';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

/* Display: Управление мероприятиями */
$handler = $view->new_display('page', 'Управление мероприятиями', 'manage_page');
$handler->display->display_options['defaults']['group_by'] = FALSE;
$handler->display->display_options['group_by'] = TRUE;
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'sl7_event manage';
$handler->display->display_options['defaults']['cache'] = FALSE;
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['defaults']['relationships'] = FALSE;
/* Связь: Ссылка на сущность: Связанная сущность */
$handler->display->display_options['relationships']['sl7_event_participants_target_id']['id'] = 'sl7_event_participants_target_id';
$handler->display->display_options['relationships']['sl7_event_participants_target_id']['table'] = 'field_data_sl7_event_participants';
$handler->display->display_options['relationships']['sl7_event_participants_target_id']['field'] = 'sl7_event_participants_target_id';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Поле: Мероприятие: Идентификатор Мероприятие */
$handler->display->display_options['fields']['eid']['id'] = 'eid';
$handler->display->display_options['fields']['eid']['table'] = 'sl7_event';
$handler->display->display_options['fields']['eid']['field'] = 'eid';
$handler->display->display_options['fields']['eid']['label'] = 'ID';
$handler->display->display_options['fields']['eid']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['eid']['alter']['path'] = 'event/[eid]';
$handler->display->display_options['fields']['eid']['separator'] = '';
/* Поле: Мероприятие: Название мероприятия */
$handler->display->display_options['fields']['label']['id'] = 'label';
$handler->display->display_options['fields']['label']['table'] = 'sl7_event';
$handler->display->display_options['fields']['label']['field'] = 'label';
$handler->display->display_options['fields']['label']['label'] = 'Название';
$handler->display->display_options['fields']['label']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['label']['alter']['path'] = 'event/[eid]';
$handler->display->display_options['fields']['label']['alter']['max_length'] = '30';
$handler->display->display_options['fields']['label']['alter']['trim'] = TRUE;
/* Поле: Мероприятие: Дата проведения */
$handler->display->display_options['fields']['sl7_event_date']['id'] = 'sl7_event_date';
$handler->display->display_options['fields']['sl7_event_date']['table'] = 'field_data_sl7_event_date';
$handler->display->display_options['fields']['sl7_event_date']['field'] = 'sl7_event_date';
$handler->display->display_options['fields']['sl7_event_date']['settings'] = array(
  'format_type' => 'short',
  'fromto' => 'both',
  'multiple_number' => '',
  'multiple_from' => '',
  'multiple_to' => '',
);
$handler->display->display_options['fields']['sl7_event_date']['group_column'] = 'entity_id';
/* Поле: Пользователь: Uid */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'users';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
$handler->display->display_options['fields']['uid']['relationship'] = 'sl7_event_participants_target_id';
$handler->display->display_options['fields']['uid']['group_type'] = 'count_distinct';
$handler->display->display_options['fields']['uid']['label'] = 'Кол-во участников';
/* Поле: Мероприятие: Мест осталось */
$handler->display->display_options['fields']['seats']['id'] = 'seats';
$handler->display->display_options['fields']['seats']['table'] = 'views_entity_sl7_event';
$handler->display->display_options['fields']['seats']['field'] = 'seats';
$handler->display->display_options['fields']['seats']['empty'] = 'Неограничено';
$handler->display->display_options['fields']['seats']['empty_zero'] = TRUE;
$handler->display->display_options['fields']['seats']['link_to_entity'] = 0;
/* Поле: Мероприятие: Стоимость участия */
$handler->display->display_options['fields']['amount']['id'] = 'amount';
$handler->display->display_options['fields']['amount']['table'] = 'sl7_event';
$handler->display->display_options['fields']['amount']['field'] = 'amount';
$handler->display->display_options['fields']['amount']['empty'] = 'Бесплатно';
$handler->display->display_options['fields']['amount']['empty_zero'] = TRUE;
$handler->display->display_options['fields']['amount']['precision'] = '0';
$handler->display->display_options['fields']['amount']['suffix'] = ' руб.';
/* Поле: Мероприятие: Действия */
$handler->display->display_options['fields']['operations']['id'] = 'operations';
$handler->display->display_options['fields']['operations']['table'] = 'sl7_event';
$handler->display->display_options['fields']['operations']['field'] = 'operations';
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Критерий сортировки: Мероприятие: Идентификатор Мероприятие */
$handler->display->display_options['sorts']['eid']['id'] = 'eid';
$handler->display->display_options['sorts']['eid']['table'] = 'sl7_event';
$handler->display->display_options['sorts']['eid']['field'] = 'eid';
$handler->display->display_options['sorts']['eid']['order'] = 'DESC';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Критерий фильтра: Мероприятие: Идентификатор Мероприятие */
$handler->display->display_options['filters']['eid']['id'] = 'eid';
$handler->display->display_options['filters']['eid']['table'] = 'sl7_event';
$handler->display->display_options['filters']['eid']['field'] = 'eid';
$handler->display->display_options['filters']['eid']['group'] = 1;
$handler->display->display_options['filters']['eid']['exposed'] = TRUE;
$handler->display->display_options['filters']['eid']['expose']['operator_id'] = 'eid_op';
$handler->display->display_options['filters']['eid']['expose']['label'] = 'ID';
$handler->display->display_options['filters']['eid']['expose']['operator'] = 'eid_op';
$handler->display->display_options['filters']['eid']['expose']['identifier'] = 'eid';
$handler->display->display_options['filters']['eid']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
);
/* Критерий фильтра: Дата: Дата (sl7_event) */
$handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['table'] = 'sl7_event';
$handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['group'] = 1;
$handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
$handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
$handler->display->display_options['filters']['date_filter']['expose']['label'] = 'Дата';
$handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
$handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
);
$handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
$handler->display->display_options['filters']['date_filter']['year_range'] = '-10:+10';
$handler->display->display_options['filters']['date_filter']['date_fields'] = array(
  'field_data_sl7_event_date.sl7_event_date_value' => 'field_data_sl7_event_date.sl7_event_date_value',
  'field_data_sl7_event_date.sl7_event_date_value2' => 'field_data_sl7_event_date.sl7_event_date_value2',
);
$handler->display->display_options['path'] = '-';
$handler->display->display_options['menu']['title'] = 'Управление мероприятиями';
$handler->display->display_options['menu']['description'] = 'Просмотр и управление мероприятиями.';
$handler->display->display_options['menu']['weight'] = '-10';
$handler->display->display_options['menu']['name'] = 'sl7-control-panel';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

/* Display: Категории */
$handler = $view->new_display('page', 'Категории', 'taxonomy_page');
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'sl7_event participation';
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '15';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Элементов на страницу';
$handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
$handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Все -';
$handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Пропустить';
$handler->display->display_options['pager']['options']['tags']['first'] = '« первая';
$handler->display->display_options['pager']['options']['tags']['previous'] = '‹ предыдущая';
$handler->display->display_options['pager']['options']['tags']['next'] = 'следующая ›';
$handler->display->display_options['pager']['options']['tags']['last'] = 'последняя »';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['style_options']['default_row_class'] = FALSE;
$handler->display->display_options['style_options']['row_class_special'] = FALSE;
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'entity';
$handler->display->display_options['row_options']['view_mode'] = 'teaser';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Контекстный фильтр: Мероприятие: Категория (sl7_event_category) */
$handler->display->display_options['arguments']['sl7_event_category_tid']['id'] = 'sl7_event_category_tid';
$handler->display->display_options['arguments']['sl7_event_category_tid']['table'] = 'field_data_sl7_event_category';
$handler->display->display_options['arguments']['sl7_event_category_tid']['field'] = 'sl7_event_category_tid';
$handler->display->display_options['arguments']['sl7_event_category_tid']['default_action'] = 'default';
$handler->display->display_options['arguments']['sl7_event_category_tid']['exception']['title'] = 'Все';
$handler->display->display_options['arguments']['sl7_event_category_tid']['default_argument_type'] = 'taxonomy_tid';
$handler->display->display_options['arguments']['sl7_event_category_tid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['sl7_event_category_tid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['sl7_event_category_tid']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['path'] = '-';

/* Display: Главная страница */
$handler = $view->new_display('page', 'Главная страница', 'front_page');
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'sl7_event participation';
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['style_options']['default_row_class'] = FALSE;
$handler->display->display_options['style_options']['row_class_special'] = FALSE;
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'entity';
$handler->display->display_options['row_options']['view_mode'] = 'teaser';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Критерий сортировки: Мероприятие: Идентификатор Мероприятие */
$handler->display->display_options['sorts']['eid']['id'] = 'eid';
$handler->display->display_options['sorts']['eid']['table'] = 'sl7_event';
$handler->display->display_options['sorts']['eid']['field'] = 'eid';
$handler->display->display_options['sorts']['eid']['order'] = 'DESC';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Критерий фильтра: Мероприятие: Дата проведения -  дата начала (sl7_event_date) */
$handler->display->display_options['filters']['sl7_event_date_value']['id'] = 'sl7_event_date_value';
$handler->display->display_options['filters']['sl7_event_date_value']['table'] = 'field_data_sl7_event_date';
$handler->display->display_options['filters']['sl7_event_date_value']['field'] = 'sl7_event_date_value';
$handler->display->display_options['filters']['sl7_event_date_value']['operator'] = '>';
$handler->display->display_options['filters']['sl7_event_date_value']['granularity'] = 'minute';
$handler->display->display_options['filters']['sl7_event_date_value']['form_type'] = 'date_popup';
$handler->display->display_options['filters']['sl7_event_date_value']['default_date'] = 'now';
$handler->display->display_options['filters']['sl7_event_date_value']['year_range'] = '-10:+10';
/* Критерий фильтра: Мероприятие: Дата проведения - дата окончания (sl7_event_date:value2) */
$handler->display->display_options['filters']['sl7_event_date_value2']['id'] = 'sl7_event_date_value2';
$handler->display->display_options['filters']['sl7_event_date_value2']['table'] = 'field_data_sl7_event_date';
$handler->display->display_options['filters']['sl7_event_date_value2']['field'] = 'sl7_event_date_value2';
$handler->display->display_options['filters']['sl7_event_date_value2']['operator'] = '>';
$handler->display->display_options['filters']['sl7_event_date_value2']['granularity'] = 'minute';
$handler->display->display_options['filters']['sl7_event_date_value2']['form_type'] = 'date_popup';
$handler->display->display_options['filters']['sl7_event_date_value2']['default_date'] = 'now';
$handler->display->display_options['filters']['sl7_event_date_value2']['year_range'] = '-10:+10';
$handler->display->display_options['path'] = '-';

/* Display: Участники */
$handler = $view->new_display('page', 'Участники', 'participants_page');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'Участники';
$handler->display->display_options['defaults']['group_by'] = FALSE;
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'sl7_event mark';
$handler->display->display_options['defaults']['cache'] = FALSE;
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['defaults']['header'] = FALSE;
/* Верхний колонтитул: Глобальный: Сводка результатов */
$handler->display->display_options['header']['result']['id'] = 'result';
$handler->display->display_options['header']['result']['table'] = 'views';
$handler->display->display_options['header']['result']['field'] = 'result';
$handler->display->display_options['header']['result']['content'] = 'Всего участников: @total';
$handler->display->display_options['defaults']['footer'] = FALSE;
$handler->display->display_options['defaults']['empty'] = FALSE;
/* Поведение при отсутствии результатов: Глобальный: Текстовая область */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = 'Нет участников.';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
$handler->display->display_options['defaults']['relationships'] = FALSE;
/* Связь: Ссылка на сущность: Связанная сущность */
$handler->display->display_options['relationships']['sl7_event_participants_target_id']['id'] = 'sl7_event_participants_target_id';
$handler->display->display_options['relationships']['sl7_event_participants_target_id']['table'] = 'field_data_sl7_event_participants';
$handler->display->display_options['relationships']['sl7_event_participants_target_id']['field'] = 'sl7_event_participants_target_id';
$handler->display->display_options['relationships']['sl7_event_participants_target_id']['required'] = TRUE;
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Поле: Пользователь: Название */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'sl7_event_participants_target_id';
/* Поле: Пользователь: E-mail */
$handler->display->display_options['fields']['mail']['id'] = 'mail';
$handler->display->display_options['fields']['mail']['table'] = 'users';
$handler->display->display_options['fields']['mail']['field'] = 'mail';
$handler->display->display_options['fields']['mail']['relationship'] = 'sl7_event_participants_target_id';
/* Поле: Мероприятие: Проверка оплаты */
$handler->display->display_options['fields']['check_paying']['id'] = 'check_paying';
$handler->display->display_options['fields']['check_paying']['table'] = 'sl7_event';
$handler->display->display_options['fields']['check_paying']['field'] = 'check_paying';
/* Поле: Мероприятие: Регистрация участника */
$handler->display->display_options['fields']['reg_participant']['id'] = 'reg_participant';
$handler->display->display_options['fields']['reg_participant']['table'] = 'sl7_event';
$handler->display->display_options['fields']['reg_participant']['field'] = 'reg_participant';
$handler->display->display_options['fields']['reg_participant']['label'] = 'Регистрация';
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Критерий сортировки: Пользователь: Uid */
$handler->display->display_options['sorts']['uid']['id'] = 'uid';
$handler->display->display_options['sorts']['uid']['table'] = 'users';
$handler->display->display_options['sorts']['uid']['field'] = 'uid';
$handler->display->display_options['sorts']['uid']['relationship'] = 'sl7_event_participants_target_id';
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Контекстный фильтр: Мероприятие: Идентификатор Мероприятие */
$handler->display->display_options['arguments']['eid']['id'] = 'eid';
$handler->display->display_options['arguments']['eid']['table'] = 'sl7_event';
$handler->display->display_options['arguments']['eid']['field'] = 'eid';
$handler->display->display_options['arguments']['eid']['default_action'] = 'default';
$handler->display->display_options['arguments']['eid']['exception']['title'] = 'Все';
$handler->display->display_options['arguments']['eid']['default_argument_type'] = 'node';
$handler->display->display_options['arguments']['eid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['eid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['eid']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['path'] = 'event/%/participants';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Участники';
$handler->display->display_options['menu']['weight'] = '-8';
$handler->display->display_options['menu']['context'] = 1;
$handler->display->display_options['menu']['context_only_inline'] = 0;

/* Display: Личный кабинет */
$handler = $view->new_display('page', 'Личный кабинет', 'user_page');
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'sl7_event participation';
$handler->display->display_options['defaults']['cache'] = FALSE;
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '15';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Элементов на страницу';
$handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
$handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Все -';
$handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Пропустить';
$handler->display->display_options['pager']['options']['tags']['first'] = '« первая';
$handler->display->display_options['pager']['options']['tags']['previous'] = '‹ предыдущая';
$handler->display->display_options['pager']['options']['tags']['next'] = 'следующая ›';
$handler->display->display_options['pager']['options']['tags']['last'] = 'последняя »';
$handler->display->display_options['defaults']['empty'] = FALSE;
/* Поведение при отсутствии результатов: Глобальный: Текстовая область */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = 'Вы не участвуете ни в одном мероприятии.
<a href="/event">Найти мероприятие</a>';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Поле: Мероприятие: Идентификатор Мероприятие */
$handler->display->display_options['fields']['eid']['id'] = 'eid';
$handler->display->display_options['fields']['eid']['table'] = 'sl7_event';
$handler->display->display_options['fields']['eid']['field'] = 'eid';
$handler->display->display_options['fields']['eid']['label'] = 'ID';
$handler->display->display_options['fields']['eid']['exclude'] = TRUE;
$handler->display->display_options['fields']['eid']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['eid']['alter']['path'] = 'event/[eid]';
$handler->display->display_options['fields']['eid']['separator'] = '';
/* Поле: Мероприятие: Название мероприятия */
$handler->display->display_options['fields']['label']['id'] = 'label';
$handler->display->display_options['fields']['label']['table'] = 'sl7_event';
$handler->display->display_options['fields']['label']['field'] = 'label';
$handler->display->display_options['fields']['label']['label'] = 'Название';
$handler->display->display_options['fields']['label']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['label']['alter']['path'] = 'event/[eid]';
/* Поле: Мероприятие: Дата проведения */
$handler->display->display_options['fields']['sl7_event_date']['id'] = 'sl7_event_date';
$handler->display->display_options['fields']['sl7_event_date']['table'] = 'field_data_sl7_event_date';
$handler->display->display_options['fields']['sl7_event_date']['field'] = 'sl7_event_date';
$handler->display->display_options['fields']['sl7_event_date']['settings'] = array(
  'format_type' => 'short',
  'fromto' => 'both',
  'multiple_number' => '',
  'multiple_from' => '',
  'multiple_to' => '',
  'show_remaining_days' => 1,
);
/* Поле: Мероприятие: Стоимость участия */
$handler->display->display_options['fields']['amount']['id'] = 'amount';
$handler->display->display_options['fields']['amount']['table'] = 'sl7_event';
$handler->display->display_options['fields']['amount']['field'] = 'amount';
$handler->display->display_options['fields']['amount']['empty'] = 'Бесплатно';
$handler->display->display_options['fields']['amount']['empty_zero'] = TRUE;
$handler->display->display_options['fields']['amount']['precision'] = '0';
$handler->display->display_options['fields']['amount']['suffix'] = ' руб.';
/* Поле: Мероприятие: Проверка оплаты */
$handler->display->display_options['fields']['check_paying']['id'] = 'check_paying';
$handler->display->display_options['fields']['check_paying']['table'] = 'sl7_event';
$handler->display->display_options['fields']['check_paying']['field'] = 'check_paying';
$handler->display->display_options['fields']['check_paying']['label'] = 'Оплата';
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Критерий сортировки: Мероприятие: Дата проведения -  дата начала (sl7_event_date) */
$handler->display->display_options['sorts']['sl7_event_date_value']['id'] = 'sl7_event_date_value';
$handler->display->display_options['sorts']['sl7_event_date_value']['table'] = 'field_data_sl7_event_date';
$handler->display->display_options['sorts']['sl7_event_date_value']['field'] = 'sl7_event_date_value';
$handler->display->display_options['sorts']['sl7_event_date_value']['order'] = 'DESC';
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Контекстный фильтр: Мероприятие: Участники (sl7_event_participants) */
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['id'] = 'sl7_event_participants_target_id';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['table'] = 'field_data_sl7_event_participants';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['field'] = 'sl7_event_participants_target_id';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['default_action'] = 'default';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['exception']['title'] = 'Все';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['default_argument_type'] = 'user';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['default_argument_options']['user'] = FALSE;
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Критерий фильтра: Дата: Дата (sl7_event) */
$handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['table'] = 'sl7_event';
$handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
$handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
$handler->display->display_options['filters']['date_filter']['expose']['label'] = 'Дата';
$handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
$handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
$handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
);
$handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
$handler->display->display_options['filters']['date_filter']['year_range'] = '-10:+10';
$handler->display->display_options['filters']['date_filter']['date_fields'] = array(
  'field_data_sl7_event_date.sl7_event_date_value' => 'field_data_sl7_event_date.sl7_event_date_value',
  'field_data_sl7_event_date.sl7_event_date_value2' => 'field_data_sl7_event_date.sl7_event_date_value2',
);
$handler->display->display_options['path'] = 'user/%/event';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Мероприятия';
$handler->display->display_options['menu']['description'] = 'Мероприятия в которых я учествую.';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

/* Display: Управление мероприятиями export */
$handler = $view->new_display('views_data_export', 'Управление мероприятиями export', 'manage_page_export');
$handler->display->display_options['defaults']['group_by'] = FALSE;
$handler->display->display_options['group_by'] = TRUE;
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'sl7_event manage';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['style_plugin'] = 'views_data_export_xls';
$handler->display->display_options['style_options']['provide_file'] = 0;
$handler->display->display_options['style_options']['parent_sort'] = 0;
$handler->display->display_options['defaults']['relationships'] = FALSE;
/* Связь: Ссылка на сущность: Связанная сущность */
$handler->display->display_options['relationships']['sl7_event_participants_target_id']['id'] = 'sl7_event_participants_target_id';
$handler->display->display_options['relationships']['sl7_event_participants_target_id']['table'] = 'field_data_sl7_event_participants';
$handler->display->display_options['relationships']['sl7_event_participants_target_id']['field'] = 'sl7_event_participants_target_id';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Поле: Мероприятие: Идентификатор Мероприятие */
$handler->display->display_options['fields']['eid']['id'] = 'eid';
$handler->display->display_options['fields']['eid']['table'] = 'sl7_event';
$handler->display->display_options['fields']['eid']['field'] = 'eid';
$handler->display->display_options['fields']['eid']['label'] = 'ID';
$handler->display->display_options['fields']['eid']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['eid']['alter']['path'] = 'event/[eid]';
$handler->display->display_options['fields']['eid']['separator'] = '';
/* Поле: Мероприятие: Название мероприятия */
$handler->display->display_options['fields']['label']['id'] = 'label';
$handler->display->display_options['fields']['label']['table'] = 'sl7_event';
$handler->display->display_options['fields']['label']['field'] = 'label';
$handler->display->display_options['fields']['label']['label'] = 'Название';
/* Поле: Мероприятие: Дата проведения */
$handler->display->display_options['fields']['sl7_event_date']['id'] = 'sl7_event_date';
$handler->display->display_options['fields']['sl7_event_date']['table'] = 'field_data_sl7_event_date';
$handler->display->display_options['fields']['sl7_event_date']['field'] = 'sl7_event_date';
$handler->display->display_options['fields']['sl7_event_date']['settings'] = array(
  'format_type' => 'short',
  'fromto' => 'both',
  'multiple_number' => '',
  'multiple_from' => '',
  'multiple_to' => '',
  'show_remaining_days' => 0,
);
/* Поле: Пользователь: Uid */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'users';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
$handler->display->display_options['fields']['uid']['relationship'] = 'sl7_event_participants_target_id';
$handler->display->display_options['fields']['uid']['group_type'] = 'count_distinct';
$handler->display->display_options['fields']['uid']['label'] = 'Кол-во участников';
/* Поле: Мероприятие: Мест осталось */
$handler->display->display_options['fields']['seats']['id'] = 'seats';
$handler->display->display_options['fields']['seats']['table'] = 'views_entity_sl7_event';
$handler->display->display_options['fields']['seats']['field'] = 'seats';
$handler->display->display_options['fields']['seats']['empty'] = 'Неограничено';
$handler->display->display_options['fields']['seats']['empty_zero'] = TRUE;
$handler->display->display_options['fields']['seats']['link_to_entity'] = 0;
/* Поле: Мероприятие: Стоимость участия */
$handler->display->display_options['fields']['amount']['id'] = 'amount';
$handler->display->display_options['fields']['amount']['table'] = 'sl7_event';
$handler->display->display_options['fields']['amount']['field'] = 'amount';
$handler->display->display_options['fields']['amount']['empty'] = 'Бесплатно';
$handler->display->display_options['fields']['amount']['empty_zero'] = TRUE;
$handler->display->display_options['fields']['amount']['precision'] = '0';
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Критерий сортировки: Мероприятие: Идентификатор Мероприятие */
$handler->display->display_options['sorts']['eid']['id'] = 'eid';
$handler->display->display_options['sorts']['eid']['table'] = 'sl7_event';
$handler->display->display_options['sorts']['eid']['field'] = 'eid';
$handler->display->display_options['sorts']['eid']['order'] = 'DESC';
$handler->display->display_options['path'] = 'control-panel/event/manage/export';
$handler->display->display_options['displays'] = array(
  'manage_page' => 'manage_page',
  'default' => 0,
  'event_page' => 0,
  'participants_page' => 0,
  'user_page' => 0,
);

/* Display: Участники export */
$handler = $view->new_display('views_data_export', 'Участники export', 'participants_page_export');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'Участники';
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'sl7_event mark';
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['style_plugin'] = 'views_data_export_xls';
$handler->display->display_options['style_options']['provide_file'] = 0;
$handler->display->display_options['style_options']['parent_sort'] = 0;
$handler->display->display_options['defaults']['relationships'] = FALSE;
/* Связь: Ссылка на сущность: Связанная сущность */
$handler->display->display_options['relationships']['sl7_event_participants_target_id']['id'] = 'sl7_event_participants_target_id';
$handler->display->display_options['relationships']['sl7_event_participants_target_id']['table'] = 'field_data_sl7_event_participants';
$handler->display->display_options['relationships']['sl7_event_participants_target_id']['field'] = 'sl7_event_participants_target_id';
$handler->display->display_options['relationships']['sl7_event_participants_target_id']['required'] = TRUE;
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Поле: Пользователь: Название */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'sl7_event_participants_target_id';
$handler->display->display_options['fields']['name']['label'] = 'Участник';
$handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
/* Поле: Пользователь: E-mail */
$handler->display->display_options['fields']['mail']['id'] = 'mail';
$handler->display->display_options['fields']['mail']['table'] = 'users';
$handler->display->display_options['fields']['mail']['field'] = 'mail';
$handler->display->display_options['fields']['mail']['relationship'] = 'sl7_event_participants_target_id';
/* Поле: Мероприятие: Проверка оплаты */
$handler->display->display_options['fields']['check_paying']['id'] = 'check_paying';
$handler->display->display_options['fields']['check_paying']['table'] = 'sl7_event';
$handler->display->display_options['fields']['check_paying']['field'] = 'check_paying';
$handler->display->display_options['fields']['check_paying']['label'] = 'Оплата';
/* Поле: Мероприятие: Регистрация участника */
$handler->display->display_options['fields']['reg_participant']['id'] = 'reg_participant';
$handler->display->display_options['fields']['reg_participant']['table'] = 'sl7_event';
$handler->display->display_options['fields']['reg_participant']['field'] = 'reg_participant';
$handler->display->display_options['fields']['reg_participant']['label'] = 'Регистрация';
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Критерий сортировки: Пользователь: Uid */
$handler->display->display_options['sorts']['uid']['id'] = 'uid';
$handler->display->display_options['sorts']['uid']['table'] = 'users';
$handler->display->display_options['sorts']['uid']['field'] = 'uid';
$handler->display->display_options['sorts']['uid']['relationship'] = 'sl7_event_participants_target_id';
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Контекстный фильтр: Мероприятие: Идентификатор Мероприятие */
$handler->display->display_options['arguments']['eid']['id'] = 'eid';
$handler->display->display_options['arguments']['eid']['table'] = 'sl7_event';
$handler->display->display_options['arguments']['eid']['field'] = 'eid';
$handler->display->display_options['arguments']['eid']['default_action'] = 'default';
$handler->display->display_options['arguments']['eid']['exception']['title'] = 'Все';
$handler->display->display_options['arguments']['eid']['default_argument_type'] = 'node';
$handler->display->display_options['arguments']['eid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['eid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['eid']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['path'] = 'event/%/participants/export';
$handler->display->display_options['displays'] = array(
  'participants_page' => 'participants_page',
  'default' => 0,
  'manage_page' => 0,
  'user_page' => 0,
);
$handler->display->display_options['sitename_title'] = 0;

/* Display: Личный кабинет export */
$handler = $view->new_display('views_data_export', 'Личный кабинет export', 'user_page_export');
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'sl7_event participation';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['style_plugin'] = 'views_data_export_xls';
$handler->display->display_options['style_options']['provide_file'] = 0;
$handler->display->display_options['style_options']['parent_sort'] = 0;
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Поле: Мероприятие: Идентификатор Мероприятие */
$handler->display->display_options['fields']['eid']['id'] = 'eid';
$handler->display->display_options['fields']['eid']['table'] = 'sl7_event';
$handler->display->display_options['fields']['eid']['field'] = 'eid';
$handler->display->display_options['fields']['eid']['label'] = 'ID';
$handler->display->display_options['fields']['eid']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['eid']['alter']['path'] = 'event/[eid]';
$handler->display->display_options['fields']['eid']['separator'] = '';
/* Поле: Мероприятие: Дата проведения */
$handler->display->display_options['fields']['sl7_event_date']['id'] = 'sl7_event_date';
$handler->display->display_options['fields']['sl7_event_date']['table'] = 'field_data_sl7_event_date';
$handler->display->display_options['fields']['sl7_event_date']['field'] = 'sl7_event_date';
$handler->display->display_options['fields']['sl7_event_date']['settings'] = array(
  'format_type' => 'short',
  'fromto' => 'both',
  'multiple_number' => '',
  'multiple_from' => '',
  'multiple_to' => '',
  'show_remaining_days' => 0,
);
/* Поле: Мероприятие: Название мероприятия */
$handler->display->display_options['fields']['label']['id'] = 'label';
$handler->display->display_options['fields']['label']['table'] = 'sl7_event';
$handler->display->display_options['fields']['label']['field'] = 'label';
$handler->display->display_options['fields']['label']['label'] = 'Название';
/* Поле: Мероприятие: Стоимость участия */
$handler->display->display_options['fields']['amount']['id'] = 'amount';
$handler->display->display_options['fields']['amount']['table'] = 'sl7_event';
$handler->display->display_options['fields']['amount']['field'] = 'amount';
/* Поле: Мероприятие: Проверка оплаты */
$handler->display->display_options['fields']['check_paying']['id'] = 'check_paying';
$handler->display->display_options['fields']['check_paying']['table'] = 'sl7_event';
$handler->display->display_options['fields']['check_paying']['field'] = 'check_paying';
$handler->display->display_options['fields']['check_paying']['label'] = 'Оплата';
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Критерий сортировки: Мероприятие: Дата проведения -  дата начала (sl7_event_date) */
$handler->display->display_options['sorts']['sl7_event_date_value']['id'] = 'sl7_event_date_value';
$handler->display->display_options['sorts']['sl7_event_date_value']['table'] = 'field_data_sl7_event_date';
$handler->display->display_options['sorts']['sl7_event_date_value']['field'] = 'sl7_event_date_value';
$handler->display->display_options['sorts']['sl7_event_date_value']['order'] = 'DESC';
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Контекстный фильтр: Мероприятие: Участники (sl7_event_participants) */
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['id'] = 'sl7_event_participants_target_id';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['table'] = 'field_data_sl7_event_participants';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['field'] = 'sl7_event_participants_target_id';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['default_action'] = 'default';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['exception']['title'] = 'Все';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['default_argument_type'] = 'user';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['default_argument_options']['user'] = FALSE;
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['sl7_event_participants_target_id']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['path'] = 'user/%/event/export';
$handler->display->display_options['displays'] = array(
  'user_page' => 'user_page',
  'default' => 0,
  'manage_page' => 0,
  'participants_page' => 0,
);
$translatables['sl7_event'] = array(
  t('Master'),
  t('Мероприятия'),
  t('ещё'),
  t('Применить'),
  t('Сбросить'),
  t('Сортировать по'),
  t('По возрастанию'),
  t('По убыванию'),
  t('Элементов на страницу'),
  t('- Все -'),
  t('Пропустить'),
  t('« первая'),
  t('‹ предыдущая'),
  t('следующая ›'),
  t('последняя »'),
  t('ID'),
  t('.'),
  t('Список мероприятий'),
  t('Календарь'),
  t('Нет мероприятий'),
  t('Нет мероприятий.'),
  t('Управление мероприятиями'),
  t('Сущность Пользователь связана через поле sl7_event_participants'),
  t('Название'),
  t('Дата проведения'),
  t('Кол-во участников'),
  t('Мест осталось'),
  t('Неограничено'),
  t(','),
  t('Стоимость участия'),
  t('Бесплатно'),
  t(' руб.'),
  t('Действия'),
  t('Дата'),
  t('Категории'),
  t('Все'),
  t('Главная страница'),
  t('Участники'),
  t('Всего участников: @total'),
  t('Нет участников.'),
  t('E-mail'),
  t('Проверка оплаты'),
  t('Регистрация'),
  t('Личный кабинет'),
  t('Вы не участвуете ни в одном мероприятии.
<a href="/event">Найти мероприятие</a>'),
  t('Оплата'),
  t('Управление мероприятиями export'),
  t('Участники export'),
  t('Участник'),
  t('Личный кабинет export'),
);
