#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//////////////////////////////////////////////////////////////////////////
// includes
//////////////////////////////////////////////////////////////////////////
#include <QMainWindow>

//////////////////////////////////////////////////////////////////////////
// namespace
//////////////////////////////////////////////////////////////////////////
class QVBoxLayout;
class QTextEdit;
class ProductObject;
class ProductTableWidget;

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;

}
QT_END_NAMESPACE
//////////////////////////////////////////////////////////////////////////
///
/// \brief      It contains all gui elements
///
//////////////////////////////////////////////////////////////////////////
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    enum Tabs
    {
        LoadAndSavePage = 0 ,
        TableWidgetPage,
    };

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createTabs();
private slots:
    void            slotBrowseClicked     ();
    void            slotLoadClicked       ();
    void            slotSaveClicked       ();

private:
    Ui::MainWindow *ui;
    QTabWidget*         m_p_tab                     = nullptr;           ///<	central widget
    QVBoxLayout*        m_p_main_layout             = nullptr;      ///<    the main window layout
    QVBoxLayout*        m_param_table_layout        = nullptr;      ///<    table window layout
    QTextEdit*          m_p_text_edit               = nullptr;      ///<   shows json datas
    std::vector<QWidget*> m_widgets_list;                           ///<    vector of the widget pointers
    QString             m_file_path;                                ///<    holds file path
    ProductObject*  m_p_product_json_object         = nullptr;       ///<    product json obj
    ProductTableWidget* m_p_product_table_widget    = nullptr;      ///<    widget which contains table in second page

};
#endif // MAINWINDOW_H
