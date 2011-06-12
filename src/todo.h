#ifndef TODO_H_
#define TODO_H_

void todo_init();
void todo_uninit();
void todo_add_task(const char *task_name, int progress);

GtkWidget* todo_get_widget();
void todo_add_task_dialog();

#endif /* TODO_H_ */
