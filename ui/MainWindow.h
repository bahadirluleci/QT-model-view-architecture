#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <vector>
#include "ui_MainWindow.h"

class ProductObject;
class ProductTableWidget;

namespace Ui {
class MainWindow;
}

/**
 * @class MainWindow
 * @brief Main application window containing all GUI components.
 *
 * The MainWindow class is responsible for managing the central interface,
 * including tab views, layout setup, file selection dialogs, and JSON data display.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// @brief Tab indices used in the main interface.
    enum Tabs {
        LoadAndSavePage = 0,
        TableWidgetPage
    };

    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

private slots:
    /// @brief Triggered when the "Browse" button is clicked.
    void onBrowseClicked();

    /// @brief Triggered when the "Load" button is clicked.
    void onLoadClicked();

    /// @brief Triggered when the "Save" button is clicked.
    void onSaveClicked();

private:
    /// @brief Initializes the tab structure inside the main window.
    void createTabs();

private:
    std::unique_ptr<Ui::MainWindow> ui;

    QTabWidget* m_tabWidget = nullptr;                  ///< Central widget containing application tabs.
    QVBoxLayout* m_mainLayout = nullptr;                ///< Main layout of the window.
    QTextEdit* m_textEdit = nullptr;                    ///< Displays JSON data as plain text.

    std::vector<QWidget*> m_tabWidgets;                 ///< List of dynamically created widgets.
    QString m_filePath;                                 ///< Stores the selected file path.

    ProductObject* m_productJsonObject = nullptr;       ///< Object containing parsed JSON product data.
    ProductTableWidget* m_productTableWidget = nullptr; ///< Widget representing the product table on second tab.
};

#endif // MAINWINDOW_H
