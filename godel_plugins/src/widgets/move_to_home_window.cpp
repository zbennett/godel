#include "godel_plugins/widgets/move_to_home_window.h"

godel_plugins::MoveToHomeWidget::MoveToHomeWidget()
{
  ui_.setupUi(this);

  //connect(ui_.PushButtonAccept, SIGNAL(clicked()), this, SLOT(accept_changes_handler()));
  //connect(ui_.PushButtonCancel, SIGNAL(clicked()), this, SLOT(cancel_changes_handler()));
  //connect(ui_.PushButtonSave, SIGNAL(clicked()), this, SLOT(save_changes_handler()));
}


void godel_plugins::MoveToHomeWidget::show()
{
  QMainWindow::show();
}

void godel_plugins::MoveToHomeWidget::update_gui_fields()
{


}

void godel_plugins::MoveToHomeWidget::update_internal_values()
{


}
