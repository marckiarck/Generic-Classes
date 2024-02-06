# Generic-Classes
Repository with the generic classes that can be used in any Unreal Engine project

## Table of Contents

> 1. [How to add this plugin to your project](#HowTo)
> 2. [Modules](#ModulesPlugin)
> 3. [Generic Classes](#GenericClassesModule)
> 4. [Generic Classes Debug](#GenericClassesDebugModule)
> 5. [Generic Classes Editor](#GenericClassesEditorModule)

<a name="HowTo"></a>
## How to add this plugin to your project
This a Unreal plugin, so you can add it to the project like a normal plugin. Anyway, below is an explanation of the steps to follow to install the plugin.

#### Add the files of this repository to the plugins folder
![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/a947f426-14ae-4c40-ab0a-0fcf0b3e28d1)

#### Add the modules to the .Target files of the project
It is important to add the editor module in the editor .Target but not in the .Target that is going to be to the shipping build beacuse then build will fail. 
![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/1c783db7-fde4-4539-b3c2-bd7462ca6089)
![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/cdbcd19e-f478-4d05-91e7-6eb226cd87f1)


#### Add the plugins modules to the uproject:
![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/1dbb55ff-c01a-446d-b886-4b41a85f157c)

<a name="ModulesPlugin"></a>
## Modules
The plugins is consolidated by three modules:
- **Generic Classes:** This is the module with the principal classes of the plugin. Here is where all the systems that will be used in the project are stored. In the shipping build this is the only modue that is going to be builded.
- **Generic Classes Debug:** This is a module that contains debug tools of the Generic Classes modules. It can be used to debug the systems and see the state of them during the execution of the program.
- **Generic Classes Editor:** This module is focused on provide tools to make easier and more confortable the implementation of the systems in Generic Classes. This tools are designed to be useful to systems that do not belong to this plugin.

<a name="GenericClassesModule"></a>
### Generic Classes

<a name="GenericClassesDebugModule"></a>
### Generic Classes Debug

<a name="GenericClassesEditorModule"></a>
### Generic Classes Editor
