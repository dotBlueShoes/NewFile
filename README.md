# NewFile 
It's a small windows application that simply creates a new file is meant to be run from within the RIGHT-CLICK-CONTEXT-MENU.

This is an old project of mine from around 2018-2019. My educational goal was to create a dialog-only application.

During this process I wanted to learn more about WinAPI subclasses, resources & manifest files. 

![alt text](https://github.com/dotBlueShoes/NewFile/blob/master/extras/media1.png?raw=true)

> *Weirdly I use this app almost everyday to create files on the fly.*

---

I run this application from within RIGHT-CLICK-CONTEXT-MENU property I've created years ago.

Eventually i will be placing a tutorial or an app that does exactly that here but for now I simply recomend searching and editing it by yourself. 

It basically involves creating a few properties in the Windows registry.

---

I recommend the use of **arrow-keys** and **enter-key** *(when done)* when in dialog popup.

Writing in `Extension Name` field is not necessary. For Example if you want to create a file named `.gitignore` you'll type all that in `File Name` property

---

### Initialize CMAKE from CMD

`.quail/cmake_refresh.bat '[PROJECT_DIR]' '[VCVARSALL_DIR]'`

### Build Profile from CMD

`.quail/build.bat '[PROJECT_DIR]' '[VCVARSALL_DIR]' 'x64-win-debug'`

`.quail/build.bat '[PROJECT_DIR]' '[VCVARSALL_DIR]' 'x64-win-release'`

### Run from CMD

`.quail/exe_with_res.ps1 '[PROJECT_DIR]\build\x64-win-debug\project\' 'NewFile'`

`.quail/exe_with_res.ps1 '[PROJECT_DIR]\build\x64-win-release\project\' 'NewFile'`
