#include "dsofinder.h"
#include "ui_dsofinder.h"

//THIS FILE CONTAINS ALL CODE FOR READING & WRITING THE CONFIG FILE AND INITIALIZATION OF THE UI

void DsoFinder::load_settings()
{
    //LOAD CONFIGFILE
    configfile = new QSettings("config.cfg",QSettings::IniFormat);      //INIT CONFIGFILE

    configfile->beginGroup("USER-SETTINGS");
    config.vid = configfile->value("version",000001).toInt();
    config.position_small = QPoint(configfile->value("pos_x",20).toInt(),configfile->value("pos_y",100).toInt());
    config.size = QSize(configfile->value("width",785).toInt(),configfile->value("height",590).toInt());
    config.ontop = configfile->value("ontop",false).toBool();
    config.waittime = configfile->value("waittime",500).toInt();
    config.show_searchtimer = configfile->value("show_searchtimer",false).toBool();
    config.items_standard_color = configfile->value("standard_color",QColor(255,0,0)).value<QColor>();
    config.items_event_color = configfile->value("event_color",QColor(220,170,40)).value<QColor>();
    config.jump_position = configfile->value("jump_position",true).toBool();
    config.stay_big = configfile->value("stay_big",false).toBool();
    config.language = configfile->value("language").toString();
    configfile->endGroup();

    configfile->beginGroup("ITEM-SETTINGS");
    config.useitems_basic = configfile->value("basic",true).toBool();
    config.useitems_adventure = configfile->value("adventure",true).toBool();
    config.use_event = configfile->value("use_event",6).toInt();
    config.usehalfsize = configfile->value("usehalfsize").toBool();
    configfile->endGroup();

    configfile->beginGroup("BACKGROUND");
    config.use_bg = configfile->value("use_bg",0).toInt();
    if(config.use_bg > bg_count) config.use_bg = bg_count;
    for(int bg_index = 0;bg_index < bg_count;bg_index++) {
        config.bg_caption.append(configfile->value(QString("bg_caption%1").arg(bg_index),"not found").value<QString>());
    }
    configfile->endGroup();

    configfile->sync();
}

void DsoFinder::populate_event_combo()
{
    ui->itemeventcomboBox->clear();

    event_data events = get_events();
    for(int i=0;i<events.eventcount;i++) {
        ui->itemeventcomboBox->addItem(events.events[i].caption);
    }
    delete [] events.events;

    ui->itemeventcomboBox->setCurrentIndex(config.use_event);
}

void DsoFinder::init_ui_options()
{
    //SET OPTION UI
    ui->ontopcheckbox->setChecked(config.ontop);
    ui->waittime_slider->setSliderPosition(config.waittime);
    ui->waittime_lineEdit->setText(QString("%1").arg(config.waittime));
    ui->searchtimercheckBox->setChecked(config.show_searchtimer);
    ui->colorstandardpushButton->setStyleSheet(QString("border-radius: 10px; background-color: rgb(%1, %2, %3);").arg(config.items_standard_color.red()).arg(config.items_standard_color.green()).arg(config.items_standard_color.blue()));
    ui->coloreventpushButton->setStyleSheet(QString("border-radius: 10px; background-color: rgb(%1, %2, %3);").arg(config.items_event_color.red()).arg(config.items_event_color.green()).arg(config.items_event_color.blue()));

    ui->itembasiccheckBox->setChecked(config.useitems_basic);
    ui->itemadventurecheckBox->setChecked(config.useitems_adventure);

    ui->halfsizecheckbox->setChecked(config.usehalfsize);

    populate_event_combo();

    ui->languagecomboBox->setCurrentText(config.language);
    select_language(config.language);
// ui->bgcomboBox->view()->setMinimumWidth(150)      ( not supported with QT 5.11.+)
    ui->bgcomboBox->setMinimumWidth(150);
    for(int i=0;i<bg_count;i++) {
        ui->bgcomboBox->addItem(QString("%1: %2").arg(i+1).arg(config.bg_caption[i]));
    }
    ui->bgcomboBox->addItem(tr("+: New Slot"));
    ui->bgcomboBox->setCurrentIndex(config.use_bg);
    if(config.use_bg >= bg_count) activate_buttons(false);
    else activate_buttons(true);

    ui->jumpcheckBox->setChecked(config.jump_position);
    ui->staybigcheckBox->setChecked(config.stay_big);
    if(config.stay_big) ui->waittimegroupbox->setDisabled(true);
}

void DsoFinder::check_version()
{
    // CHANGE SETTINGS WHEN UPDATING TO NEW VERSION
    if(config.vid != cvid) {
        if(config.vid > 000001 && config.vid < 140528) {
            // REMOVE OLD DATA FROM CONFIG FILE
            configfile->beginGroup("ITEM-SETTINGS");
            configfile->remove("halloween13");
            configfile->remove("christmas13");
            configfile->remove("eastern14");
            configfile->endGroup();
        }

        if(config.vid < 140825) { // CHANGES FOR NEW BACKGROUND HANDLING
            if(QFile::exists("background.png")) {
                if(QFile::rename("background.png","background0.png")) {
                    config.use_bg = 0;
                    if(bg_count == 0) {
                        config.bg_caption.append("old background image");
                        bg_count++;
                    }
                }
            }
        }
        config.use_event = 6;
        config.vid = cvid;
    }
}

void DsoFinder::save_settings()
{
    configfile->beginGroup("USER-SETTINGS");
    configfile->setValue("version",config.vid);
    configfile->setValue("pos_x",config.position_small.x());
    configfile->setValue("pos_y",config.position_small.y());
    configfile->setValue("width",config.size.width());
    configfile->setValue("height",config.size.height());
    configfile->setValue("ontop",config.ontop);
    configfile->setValue("waittime",config.waittime);
    configfile->setValue("show_searchtimer",config.show_searchtimer);
    configfile->setValue("standard_color",config.items_standard_color);
    configfile->setValue("event_color",config.items_event_color);
    configfile->setValue("jump_position",config.jump_position);
    configfile->setValue("stay_big",config.stay_big);
    configfile->setValue("language",config.language);
    configfile->endGroup();

    configfile->beginGroup("ITEM-SETTINGS");
    configfile->setValue("basic",config.useitems_basic);
    configfile->setValue("adventure",config.useitems_adventure);
    configfile->setValue("use_event",config.use_event);
    configfile->setValue("usehalfsize",config.usehalfsize);
    configfile->endGroup();

    configfile->beginGroup("BACKGROUND");
    configfile->setValue("use_bg",config.use_bg);
    for(int bg_index = 0;bg_index < bg_count;bg_index++) {
        configfile->setValue(QString("bg_caption%1").arg(bg_index),config.bg_caption[bg_index]);
    }
    configfile->endGroup();

    configfile->sync();
}

