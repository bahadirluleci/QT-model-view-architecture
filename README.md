# QT-model-view-architecture
Model-View-Controller (MVC) is a design pattern originating from Smalltalk that is often used when building user interfaces.

You can get detailed information from [QT Documentation](https://doc.qt.io/qt-5/model-view-programming.html)

## Now let's talk about using our own custom model-view widget.

![Untitled](https://user-images.githubusercontent.com/73167603/145189276-9f9712ac-a62c-44e8-aea1-00ba19f1a4ba.png)

- The purpose of the application is to create a model-view pattern on a QtableView according to the given Json configuration file.
- On the 4th column formed on QtableView, the use of delegate is also included. 
- In order for this delegate to change the values, some methods have been added in the delegate and model class.
- It is allowed to save the Json file in its new format again after the values are changed in the delegate.

# Usage of Widget
- Browse with "Browse... button" releted Json configuration file.
- Click Load... Button after browse operation. This button connected with load operations and if the file format is correct the file text shows on the QTextEdit.
- You are ready to go second page. After clicking second page of QTabWidget you can manipulate values in the delegete. The other values are read-only. 
- After changing values you can save new file with .json extension. To save file go first page and click Save... button.
