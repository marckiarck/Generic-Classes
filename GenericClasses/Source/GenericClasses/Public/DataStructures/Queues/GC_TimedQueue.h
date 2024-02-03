// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GenericClasses/Public/DataStructures/GC_Node.h"


template <typename T>
class GENERICCLASSES_API GC_TimedNode 
{
	GENERATE_NODE_BODY(GC_TimedNode, T);

public:
	GC_TimedNode(T* nodeObject, float popTime) : storedObject(nodeObject), popTime(popTime)
	{
	};

public:
	float popTime = 0.f;

};


template <typename T>
class GENERICCLASSES_API TGC_TimedQueue
{
	
private:
	GC_TimedNode<T>* firstNode = nullptr;
	GC_TimedNode<T>* lastNode = nullptr;

public:
	void Enqueue(T* queuedObject, float popTime = 0.f)
	{
		if (queuedObject == nullptr)
		{
			return;
		}

		GC_TimedNode<T>* queuedNode = new GC_TimedNode<T>(queuedObject, popTime);

		if (firstNode == nullptr)
		{
			firstNode = queuedNode;
			lastNode = queuedNode;
		}
		else
		{
			if (lastNode->popTime < popTime)
			{
				lastNode->nextNode = queuedNode;
				queuedNode->previousNode = lastNode;
				lastNode = queuedNode;
			}
			else
			{
				GC_TimedNode<T>* currentNode = firstNode;
				while (currentNode != nullptr)
				{
					if (currentNode->popTime > popTime)
					{
						if (GC_TimedNode<T>* previousNode = currentNode->previousNode)
						{
							previousNode->nextNode = queuedNode;
							queuedNode->previousNode = previousNode;
						}
						else
						{
							firstNode = queuedNode;
						}

						queuedNode->nextNode = currentNode;
						currentNode->previousNode = queuedNode;

						return;
					}

					GC_TimedNode<T>* nextNode = currentNode->nextNode;
					if (nextNode)
					{
						currentNode = nextNode;
					}
					else
					{
						currentNode->nextNode = queuedNode;
						queuedNode->previousNode = currentNode;
						return;
					}
				}
			}
		}
	};

	void Dequeue(float timeStep, TArray<T*>& returnArray)
	{
		returnArray.Empty();

		GC_TimedNode<T>* currentNode = firstNode;
		GC_TimedNode<T>* deletedNode = nullptr;
		while (currentNode)
		{
			if (currentNode->popTime < timeStep)
			{
				returnArray.Add(currentNode->Get());
				deletedNode = currentNode;
				currentNode = currentNode->nextNode;

				if (deletedNode)
				{
					firstNode = currentNode;
					//No need to control lastNode beacuse the only new value that can take in dequeue is nullptr 
					//that will be set with delete
					delete deletedNode;
				}
			}
			else
			{
				currentNode->popTime -= timeStep;
				currentNode = currentNode->nextNode;
			}
		}
	};

	void GetQueueArray(TArray<T*>& returnArray) 
	{
		returnArray.Empty();

		GC_TimedNode<T>* currentNode = firstNode;
		while (currentNode)
		{
			returnArray.Add(currentNode->Get());
			currentNode = currentNode->nextNode;
		}
	};
};

