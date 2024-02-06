# Generic-Classes
Repository with the generic classes that can be used in any Unreal Engine project

## Table of Contents

> 1. [How to add this plugin to your project](#HowTo)

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

