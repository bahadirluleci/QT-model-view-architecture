#include "MainWindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QFileDialog>
#include <QDebug>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QFrame>

#include "ProductObject.h"
#include "ProductTableWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(std::make_unique<Ui::MainWindow>()),
    m_productJsonObject(new ProductObject(this)),
    m_productTableWidget(new ProductTableWidget(this))
{
    ui->setupUi(this);

    createTabs();
}


void MainWindow::createTabs()
{
    m_tabWidget = new QTabWidget(this);
    setCentralWidget(m_tabWidget);
    m_tabWidget->setObjectName("CentralTab");

    // Tab 1: Load and Save
    QFrame* frame = new QFrame(this);
    m_mainLayout = new QVBoxLayout();
    frame->setLayout(m_mainLayout);

    auto* browseButton = new QPushButton("Browse...", this);
    auto* loadButton = new QPushButton("Load...", this);
    auto* saveButton = new QPushButton("Save...", this);

    m_textEdit = new QTextEdit(this);
    m_textEdit->setReadOnly(true);

    m_mainLayout->addWidget(browseButton);
    m_mainLayout->addWidget(loadButton);
    m_mainLayout->addWidget(m_textEdit);
    m_mainLayout->addWidget(saveButton);

    m_tabWidgets.push_back(frame);
    m_tabWidget->insertTab(Tabs::LoadAndSavePage, m_tabWidgets[Tabs::LoadAndSavePage], "Load and Save");

    // Second tab: Table
    m_tabWidgets.push_back(m_productTableWidget);
    m_tabWidget->insertTab(Tabs::TableWidgetPage, m_tabWidgets[Tabs::TableWidgetPage], "Product Table");

    // button connections
    connect(browseButton, &QPushButton::clicked, this, &MainWindow::onBrowseClicked);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadClicked);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveClicked);
}

void MainWindow::onBrowseClicked()
{
    m_filePath = QFileDialog::getOpenFileName(this, tr("Open Configuration File"),
                                            QDir::homePath(), tr("JSON Files (*.json)"));
}


void MainWindow::onLoadClicked()
{
    if (m_filePath.isEmpty() || !m_productJsonObject)
        return;

    m_productJsonObject->load(m_filePath);

    QJsonDocument doc(m_productJsonObject->getProductObject());
    m_textEdit->setText(doc.toJson());


    if (m_productTableWidget)
        m_productTableWidget->setData(m_productJsonObject->getProductObject());

    m_filePath.clear();

}

void MainWindow::onSaveClicked()
{
    if (!m_productTableWidget)
        return;

    QString savePath = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    QDir::homePath(), tr("JSON Files (*.json)"));

    if (savePath.isEmpty())
        return;

    QFile file(savePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Unable to open file for writing.";
        return;
    }

    QJsonDocument doc(m_productTableWidget->data());
    file.write(doc.toJson());
    file.close();
}
