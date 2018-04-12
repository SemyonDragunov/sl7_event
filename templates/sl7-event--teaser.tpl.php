<div class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <figure>
    <a href="<?php print SL7_EVENT_PATH . '/' . $variables['element']->eid; ?>">
      <img src="<?php print image_style_url('sl7_event_teaser', $variables['element']->sl7_event_image['und'][0]['uri']); ?>" />
    </a>
  </figure>

  <div class="description">
    <article>

      <?php print render($title_prefix); ?>
      <h3<?php print $title_attributes; ?>><a href="<?php print SL7_EVENT_PATH . '/' . $variables['element']->eid; ?>"><?php print $variables['element']->label; ?></a></h3>
      <?php print render($title_suffix); ?>

      <?php if (isset($event_state) && 'end' == $event_state): ?>
        <div class="state">Мероприятие закончилось</div>
      <?php elseif (isset($event_state) && 'start' == $event_state): ?>
        <div class="state">Мероприятие уже началось</div>
      <?php elseif (isset($event_state) && 'no_seats' == $event_state): ?>
        <div class="state">Мест нет</div>
      <?php endif; ?>

      <ul class="property">
        <li><span>Дата проведения:</span> <?php print $date_start; ?></li>
        <?php if (!empty($variables['element']->sl7_event_category)): ?>
          <li><span>Категория:</span> <?php print $category; ?></li>
        <?php endif; ?>

        <?php if ((isset($event_state) && 'start' == $event_state) || !isset($event_state)): ?>
          <?php if (module_exists('sl7_payment')): ?>
            <li><span>Стоимость:</span> <?php print $amount = ($variables['element']->amount == 0) ? 'Бесплатно' : $variables['element']->amount . ' руб.'; ?></li>
          <?php endif; ?>
          <li><span>Мест осталось:</span> <?php print $seats = ($variables['element']->seats == 0) ? 'Неограниченно' : $variables['element']->seats; ?></li>
        <?php endif; ?>
      </ul>

      <div class="body" <?php print $content_attributes; ?>>
        <p><?php print truncate_utf8(check_plain(strip_tags($variables['element']->sl7_event_body['und'][0]['safe_value'])), 250, FALSE, TRUE); ?></p>
      </div>

    </article>
  </div>

</div>