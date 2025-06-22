# Qt Model-View Architecture Example

This project demonstrates a clean and extensible implementation of the **Qt Model-View-Delegate** architecture using `QStandardItemModel`, custom delegates, and JSON-based data binding. It serves as a practical template for building dynamic, editable Qt-based UIs with rich data handling logic.

---

## 🔧 Features

- ✅ **Model-View separation** using `QTableView` and `ProductModel`
- ✅ **Custom delegate** for checkbox interaction (`ProductDelegate`)
- ✅ **Data binding to JSON** objects via `ProductItem`
- ✅ **User-friendly UI** for browsing and loading `.json` configuration files
- ✅ **Modern C++ practices** (smart pointers, constexpr constants, clean encapsulation)
- ✅ **Doxygen-ready** class documentation

---

## 🗂️ Project Structure

```
QT-model-view-architecture/
├── delegate/
│   └── ProductDelegate.{h,cpp}     # Custom rendering and editing behavior
├── model/
│   ├── ProductModel.{h,cpp}        # Model logic using QStandardItemModel
│   ├── ProductItem.{h,cpp}         # Wrapper item for JSON data and roles
│   └── ProductObject.{h,cpp}       # JSON file parsing and validation
├── ui/
│   └── MainWindow.{h,cpp,ui}       # GUI logic and file integration
├── Constants.h                     # Application-wide string keys
├── main.cpp                        # Application entry point
```

---

## 🖥️ Usage

1. Build the project using **Qt Creator** or `CMake` with **Qt 6.x**
2. Run the application
3. Click **Browse** to select a `.json` configuration file
4. Click **Load** to parse and display the data in a table
5. Toggle checkboxes (e.g., availability) inline
6. Edits update the underlying JSON model

---

## 📦 Requirements

- Qt 6.x (tested on 6.6+)
- C++17 or later
- CMake 3.16+ (if building manually)

---

## 📚 Documentation

Inline Doxygen comments are available for core classes (`ProductItem`, `ProductModel`, `ProductDelegate`, etc.). You can generate HTML documentation with:

```bash
doxygen Doxyfile
```

---

## 📁 Example JSON Format

```json
{
  "product": {
    "id": "1234",
    "name": "Demo Widget",
    "price": 42,
    "available": true
  }
}
```

---

## 🧠 Learning Outcomes

- How to structure Qt projects with **Model-View-Delegate** separation
- How to use `QStandardItem` and custom roles
- How to integrate JSON into a Qt-based table UI
- How to extend Qt delegates for interactive widgets like checkboxes

---

## 📃 License

This project is released under the MIT License.
