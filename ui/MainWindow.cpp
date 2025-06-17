#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QFileDialog>
#include <QDebug>
#include "ProductObject.h"
#include <QJsonDocument>
#include "ProductTableWidget.h"

//////////////////////////////////////////////////////////////////////////
/// \brief      Constructor
//////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_p_product_json_object  = new ProductObject(this);
    m_p_product_table_widget  = new ProductTableWidget(this);
    createTabs();
}
//////////////////////////////////////////////////////////////////////////
/// \brief      Destructor
//////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow()
{
    delete ui;
}

//////////////////////////////////////////////////////////////////////////
///
///	\brief	Create central widget with tabs
///	\return
///
//////////////////////////////////////////////////////////////////////////
void MainWindow::createTabs()
{
    //create
    m_p_tab = new QTabWidget(this);
    m_p_tab->setObjectName("CentralTab");

    QFrame * p_frame = new QFrame(this);

    m_p_main_layout = new QVBoxLayout();
    p_frame->setLayout(m_p_main_layout);
    QPushButton * p_b_browse = new QPushButton("Browse...", this);
    QPushButton * p_b_load = new QPushButton("Load...", this);
    QPushButton * p_b_save = new QPushButton("Save...", this);

    m_p_text_edit = new QTextEdit();
    m_p_text_edit->setReadOnly(true);

    connect(p_b_browse, &QPushButton::clicked, this, &MainWindow::slotBrowseClicked);
    connect(p_b_load, &QPushButton::clicked, this, &MainWindow::slotLoadClicked);
    connect(p_b_save, &QPushButton::clicked, this, &MainWindow::slotSaveClicked);

    m_p_main_layout->addWidget(p_b_browse);
    m_p_main_layout->addWidget(p_b_load);
    m_p_main_layout->addWidget(m_p_text_edit);
    m_p_main_layout->addWidget(p_b_save);


    //Widget
    m_widgets_list.push_back(p_frame);
    m_p_tab->insertTab(Tabs::LoadAndSavePage, m_widgets_list[Tabs::LoadAndSavePage], "LoadAndSavePage");

    //TableWidget
    m_widgets_list.push_back(m_p_product_table_widget);
    m_p_tab->insertTab(Tabs::TableWidgetPage, m_widgets_list[Tabs::TableWidgetPage], "ProductTable");

    this->setCentralWidget(m_p_tab);
}

//////////////////////////////////////////////////////////////////////////
///
/// \brief  Slot for clicking browse button
/// \return void
///
//////////////////////////////////////////////////////////////////////////
void MainWindow::slotBrowseClicked()
{
    QString dialog_title = "Open Configuration File";
    QString home_dir = "/home";
    QString extension_filter = "JSON File (*.json)";
    QString file_name = QFileDialog::getOpenFileName(this, dialog_title,
                                                     home_dir,
                                                     extension_filter);
    if (true == file_name.isEmpty())
        return;
    m_file_path = file_name;
}

//////////////////////////////////////////////////////////////////////////
///
/// \brief  Slot for clicking load button
/// \return void
///
//////////////////////////////////////////////////////////////////////////
void MainWindow::slotLoadClicked()
{
//    if(m_p_table_widget == Q_NULLPTR)
//        return;

    QDir dir(m_file_path);
    if(true == m_file_path.isEmpty())
    {
        this->m_file_path = dir.absolutePath();
    }
    if(m_p_product_json_object == nullptr)
        return;
    m_p_product_json_object->load(m_file_path);
    QJsonDocument document(m_p_product_json_object ->getProductObject());
    m_p_text_edit->setText(document.toJson());
    m_file_path.clear();

    m_p_product_table_widget->setData(m_p_product_json_object->getProductObject());
}

//////////////////////////////////////////////////////////////////////////
///
/// \brief  Slot for clicking save button
/// \return void
///
//////////////////////////////////////////////////////////////////////////
void MainWindow::slotSaveClicked()
{
    if (nullptr == m_p_product_json_object )
        return;

    QString file_dialog_title = "Save File";
    QString home_dir = "/home";
    QString extension_filter = "JSON File (*.json)";
    QString document_name = QFileDialog::getSaveFileName(this, file_dialog_title,
                                                     home_dir,
                                                     extension_filter);
    if (document_name.isEmpty())
        return;
    if (nullptr == m_p_product_table_widget )
        return;
    QJsonObject table_json_data = m_p_product_table_widget->data();
    QFile file(document_name);
    QJsonDocument document(table_json_data);
    if(false == file.open(QIODevice::WriteOnly))
    {
        qWarning() << "Document can not open";
    }
    file.write(document.toJson());
    file.close();
}
