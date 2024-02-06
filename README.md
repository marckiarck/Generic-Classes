# Generic-Classes
Repository with the generic classes that can be used in any Unreal Engine project

## Table of Contents
1. [How to add this plugin to your project](#HowTo)
   
2. [Modules](#ModulesPlugin)
   
3. [Generic Classes](#GenericClassesModule)

  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.1 [Singleton Register](#GenericClassesModule-SR)
  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.2 [Object Pooler](#ObjectPooler)
  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.3 [Event System](#EventSystem) 
  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.3.1 [Events](#EventSystem-Events)
   
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.3.2 [Event Register](#EventSystem-EventRegister)
   
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.3.3 [Event Sequence](#EventSystem-EventSequence)
   
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.4 [Condition System](#ConditionSystem) 
  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.5 [Game Data](#GameData)
  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.6 [Data Structures](#DataStructures) 
  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.7 [Debug System](#DebugSystem) 
  
4. [Generic Classes Debug](#GenericClassesDebugModule)
5. [Generic Classes Editor](#GenericClassesEditorModule)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5.1 [Editor Component System](#EditorComponent)
  
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
The plugins is consolidated by **three modules:**
- **Generic Classes:** This is the module with the principal classes of the plugin. Here is where all the systems that will be used in the project are stored. In the shipping build this is the only modue that is going to be builded.
- **Generic Classes Debug:** This is a module that contains debug tools of the Generic Classes modules. It can be used to debug the systems and see the state of them during the execution of the program.
- **Generic Classes Editor:** This module is focused on provide tools to make easier and more confortable the implementation of the systems in Generic Classes. This tools are designed to be useful to systems that do not belong to this plugin.

<a name="GenericClassesModule"></a>
## Generic Classes
This module contains systems than can be useful for every project and offer ways to implement behaviors and design patterns in a simple and scalable way (like Singletons)

<a name="GenericClassesModule-SR"></a>
### Singleton Register
This system allows to create a **singleton** of every Unreal class (classes that **inherits form UObject**). The user has to implement nothing to make his own classes become singletons.

The singleton instances can be accesed throught **Blueprint:**

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/15031513-19f6-40d7-b0fd-152fdf3b80c5)

Can also be accessed in **code** calling the method:
![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/dc61bae2-b599-402a-ac9f-d238e153afac)

There is an **Unreal Interface** called **GC_Singleton** that can be inherited by classes to override methods called when singleton is getted, reseted and instanced by GetInstance methods.

> [!WARNING]
> **Disclaimer**: the singletons obtainer this way ensures that the user gets the same instance of an object always the classes are accessed by the Singleton Register system, but **the user can create other instances** of that classes and is up to the user whether this should be done or not.

<a name="ObjectPooler"></a>
### Object Pooler
An **object pooler** is a system that provides an instance getted from a **prepared pool of instanes**. This allows to create this instances when the project starts running and acces them in the future with out the need of create new objects (which affects to the **performance**). 

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

> [!WARNING]
> This system must be used with **extreme caution** beacuse the references to the objects returned to the pool will no become nullprt but will **point to useless objects** (beacuse they are inside the pool). When an object is returned to the pool the **references** pointing to it must be maunally make them **point to nullptr.**

<a name="EventSystem"></a>
### Event System
This is the typical event system that always is needed to implement. This system usualy consists in **atomic behaviours that provides complex behaviours when they are working all together.**

An example could be an ability of a fighting game. The complex behaviour is the attach ability, which is made up of atomic events like play an animation, cast a sweep to detect who are affected by the attack, apply the damage and spawn paricle effects or display UI feedback. 

<a name="EventSystem-Events"></a>
#### Events
To make this system as generic and scalable as needed in each project there is a base class called **GC_Event** that can be inherited to gave them the desired behaviour.

The **overrideable methods** are:

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/339751ef-0576-4d21-b2e7-de5db8044524)


But this events are **planned to be used by its delegates** calls:

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/951d6f8e-9ed6-402a-ae24-ccc54eab6c02)

This will allow the **Object Pooler** to **reuse finished events** to create new events getting them out of the pool and clearing the delegates. This will **reduce** a lot the **performance impact** and will make them a really cheap resource.

An example of how to use them by **delegates:**

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/8e82e35c-a722-4963-9abd-909fbf32e914)

This events can be implemented in **Blueprints** to inheriting from **GC_BlueprintEvent:**

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/9c443c09-651c-4703-8d9f-c91c3a144ac8)

<a name="EventSystem-EventRegister"></a>
#### Event Register
The events must be **registered** in the **Event Register** to **start working.**

This can be done in **Blueprints** calling the node **Register Event:**

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/b35c3c18-91e9-4bc5-908f-2c86c6501b41)

And in **code:**

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/78aea16c-8d0d-4575-9762-228f65410031)

For **Blueprits** there are the nodes **Wait Delay** and **Delegate Event Tick** that implments behaviours that can be useful in diferent ways:

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/e41ac618-4c67-4b2b-a5d9-a8f481175c12)

<a name="EventSystem-EventSequence"></a>
#### Event Sequence
It may happend that is needed to **launch a succession of events one after anorther**. To make this situation as light as possible there is the **Event Sequence**. By creating a DataAsset of **GC_EventSequenceDataAsset** and customizing it, the Event Sequences can be configurated.

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/e0e02d38-6636-461b-9edd-a8f353675482)

The **Event Sequence**s can be launched by **Blueprints:**

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/56e5b142-8c5e-4b8e-9438-2b217951ea0c)

And by **code:**

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/2d9530df-04ee-4c32-a809-6187a1040d0c)

<a name="ConditionSystem"></a>
### Condition System
The Condition System offers a wrapper to condition sentences converting them in UObjects. This allows conditions to be integrated into other systems in a generic and scalable way.

An example can be this Actor Spawner System (not included in the plugin) that can modifiy when to spawn an Actor based on a condition of the Condition System:

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/641d8a2c-7575-4ee7-8ee6-b19d50538c29)

#### Condition Sentence 
There is a class called **GC_ConditionSentence**. This is the **parent class** from which inherits the rest of the **coditions of the Condition System**. This class has a virtual method called **RunConditionSentence()** that can be **overriden** to formulate the desired condition. This class also has a **delegate** that **notifies** to the subscribed classes the **result** of this method.

There is one more method called **SetConditionData()**. A condition may **need addiotnal data** to decide the result of the condition. To allow this without affecting the generic nature of the condition sentences **this method can be overriden**. Through this method each **condition sentence can handle data** out of its scope transparently to whoever invokes it.

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/50960103-211f-4436-99e9-f3846c33ca5f)

>[!Note]
>To run condition sentences the method that should be called is CheckCondition() (it does more operations than call RunConditionSentence)

>[!Note]
>To implement condition sentences in **Blueprint** there is a class called **GC_BlueprintConditionSentence**  to inherit from it.

Condition System provides two nodes called **Check Condition** and **Wait Condition Success** that can be useful in many situations:

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/502c09a5-06dc-4dd5-9ac5-b28a27aa5e5d)

<a name="GameData"></a>
### Game Data
In all projects there is always the need to **store** some **data** to obtain them later and make operations (like the player or an array of enemies). The **Game Data** is a class created to **solve the problem** of implement a new class of this kind in every project. **Game Data** offers an space to **store** data and 
**access** them in a fast way with no need of implementing anything.

Game Data has the methods **SaveData** and **GetData** to save and recover data.

This methods can be called in **Blueprints:**

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/c70d2a80-367c-4a0a-be6d-371e35a6d894)

And in **code:**

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/43e99473-f681-42c5-a564-40bc7effc37f)

##### Data Actor Component
To make as **confortable** as possible to add **Actors** to the **Game Data** there is an **actor component** called **DataActorComponent** that adds the actor to the Game Data when it is spawned.

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/751e6503-048f-4e3c-a72d-c37bef594785)

>[!Warning]
>This system relies a lot in the user. It will not prevent them from override data that are registered with an existing data identifier even if the class of the passed object is different.

<a name="DataStructures"></a>
### Data Structures
There is a folder in Generic Classes called **Data Structures**. This folder stores data structures that were **used in past projects** and could be **useful in future projects.**

This data structures are:
##### Timed Queue:
This **queue** works like a normal queue but instead of having a FIFO behaviour, it **decides** how the queue is going to **dequeue objects based on a time value** that represents when the queued objects must leave the queue.

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/bd48e006-14c1-4972-86d2-d6d0629ec738)

**To dequeue elements a "pop time" must be passed** to the queue. The queue will **push** out all the elements that were **waiting that time or less** to be expelled. The returned elements will be sorted by the remaining time in the queue.

A visual example passing 3 units of "pop time" to the queue of the previous visual example:

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/c2b4ca22-52f7-4611-a656-206679c1f210)

<a name="DebugSystem"></a>
### Debug System
>[!Note]
>This system is currently being developed and is planned to make it become bigger and more useful

This system allows the user to add debug messages in the code that will notify that something is not working as spected. Currently works the same as UE_LOG nbut adding an Slate notification.

<a name="GenericClassesDebugModule"></a>
## Generic Classes Debug
This module is conformed by debug classes that offers information of the state of the systems. It contains two types of classes:

#### Debugger Categories
All the debugger categories of the systems implemented in Generic Classes module. This categories allows to consult launched and registered events, classes made singleton the state of the pools of the Object Pooler,...

#### Debug Objects
>[!Note]
>This system is currently being developed and is planned to make it become bigger and more useful

**GC_DebugObject** is an interface designed to offer the posibility of create **debug objects** that can be used to **show debug information** in diferent ways. Currently the only system than uses this objects is the **Debug Objects Category**. This is a **debugger category** that can show data from any Debug Object. This is a category designed to make **cleaner** the **debug information showed**. To achieve this the **Debug Objects Category shows the debug information of only one Debug Object**, but the object used by the Debug Objects Category can be **switched** in any moment by using the **command EnableDebugObject(FString)** and passing it the **name of the class** of the **Debug Object** that is wanted to use as reference to the Debug Objects Category.

<a name="GenericClassesEditorModule"></a>
## Generic Classes Editor
This is a module that contains tools that is going to be useful for thigs related with the editor. Currently it has two systems:

<a name="EditorComponent"></a>
### Editor Component System
This system ofer a parent class called **GC_EditorComponent**. This is an **actor component** that is going to be **added to the objects selected in the editor**. This component is **not serialized** and **will not be saved**. Inside this editor components the user can implement methods that will be useful in editor but there is no need to have them in the shipping build (like clone objects or safe destroying them).

The **GC_EditorComponent** has a method called **IsValidComponent()** that can be overriden to **check** if the editor component **should be added** to the **selected object** or not.

This component is **accesible** in the **Details panel** and its methods can be accessed there.

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/8aa650a5-00e1-4681-8d08-2957389b7257)

Projects were this module is added will also include a **DataAsset** called **DT_EditorComponents**. In this DataAsset the user has to **configure the editor component classes** to decide if it is wanted to add editor components to selected objects or not (maybe the user has created a week ago a editor component for AI and now he do not need it but do not want to delete in case he need it later).

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/817e65f5-88f3-41de-b63f-9d1a5726ca58)

### K2Node_GC_BaseNode
This is a class that inherits from K2Node. K2Node_GC_BaseNode is implemented to allow create a node from any function. The node created using the Base Node will create all the parameters of the function and the delegates also (even delegates with parameters).

There are some functions that can be extended to Blueprints just adding the BlueprintCallable UFUNCTION specifier. The Base Node exists to offer a easy way to expose to Blueprints this functions.

To use K2Node_GC_BaseNode the user just need to inherit from it and override the method called GetMainNodeFunction. Here is an example of how to override this method:

![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/20ef2568-89e4-469d-8bef-772cdd464f0c)

The function used in classes that inherits from this class can be modified and the node will fit to its new signature, but all the Blueprints were the node of the modified function is used should be recompiled to work again.

>[!Warning]
>K2Nodes are very unscalables by default. The GetNodeTitle(), GetTooltipText() and GetMenuCategory() methods must be overriden when inheriting from K2Node_GC_BaseNode.
>
>![image](https://github.com/marckiarck/Generic-Classes/assets/13780925/bb21e219-968b-49cd-acb7-3ddff7af2fb6)
