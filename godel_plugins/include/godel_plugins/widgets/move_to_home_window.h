#ifndef MOVE_TO_HOME_WINDOW_H
#define MOVE_TO_HOME_WINDOW_H

#include <godel_plugins/widgets/parameter_window_base.h>
#include <ui_move_to_home_window.h>

namespace godel_plugins
{

class MoveToHomeWidget : public ParameterWindowBase
{
  Q_OBJECT
public:
    MoveToHomeWidget();
    virtual void show();

protected:

    virtual void update_gui_fields();

    virtual void update_internal_values();
  Ui::MoveToHomeWindow ui_;
};

}

#endif // MOVE_TO_HOME_WINDOW_H
