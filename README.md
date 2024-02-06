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
This module contains systems than can be useful for every project and offer ways to implement behaviors and design patterns in a simple and scalable way (like Singletons)

#### Singleton Register
This system allows to create a **singleton** of every Unreal class (classes that **inherits form UObject**). The user has to implement nothing to make his own classes become singletons. Even so I mut make a **disclaimer**: the singletons obtainer this way ensures that the user gets the same instance of an object always the classes are accessed by the Singleton Register system, but **the user can create other instances** of that classes and is up to the user whether this should be done or not.

The singleton instances can be accesed throught **Blueprint:**

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/15031513-19f6-40d7-b0fd-152fdf3b80c5)

Can also be accessed in **code** calling the method:
![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/dc61bae2-b599-402a-ac9f-d238e153afac)

There is an **Unreal Interface** called **GC_Singleton** that can be inherited by classes to override methods called when singleton is getted, reseted and instanced by GetInstance methods.

#### Object Pooler
An **object pooler** is a system that provides an instance getted from a **prepared pool of instanes**. This allows to create this instances when the project starts running and acces them in the future with out the need of create new objects (which affects to the **performance**). This system must be used with **extreme caution** beacuse the references to the objects returned to the pool will no become nullprt but will **point to useless objects** (beacuse they are inside the pool).

The Object Pooler works with **UObjects** and **AActors** in different ways.
To create **UObjects** in **Blueperints:**
![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/87b78e35-3abd-4bba-b23e-34046b699b4a)

And in **code:**
![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/2da7a9d3-8ab2-4c87-a3d2-3350a94b4ded)

To create **AActors** in **Blueprints:**
![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/f5fea255-d7f1-4093-bb4d-337401071290)

And in **code:**
![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/a267c3eb-5289-4e0c-b6be-85a5f53f5891)

The method to **return the objects to the pool** is also different for **AActors** and **UObjects.**
To destroy **UObjects** in **Blueprints:**
![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/cd14e6cb-69ec-45b9-a75b-430c53dd719e)

And in **code:**
![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/050617bb-90cf-49ff-8d6f-ddb3729b0ffa)

To destroy **AActors** in **Blueprints:**
![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/3140ff22-c089-42e3-8891-412ca585165b)

And in **code:**
![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/6a3c393a-cd84-4441-a068-378140116925)

When this methods are called a **DatatableRowHandle** can be passed as **parameter.** This parameter can be used to **customize the creation of the object**. To make this customization the created obect must **inherit** from the Unreal interface **GC_PooledObjectInterface** and override its methods.

#### Event System
#### Condition System
#### Game Data
#### Data Structures
#### Debug System

<a name="GenericClassesDebugModule"></a>
### Generic Classes Debug

<a name="GenericClassesEditorModule"></a>
### Generic Classes Editor
