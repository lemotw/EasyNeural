# EasyNeural

EasyNeural is a library to simulate neural net.
It doesn't like such Caffe powerful.
But it works in an exact and it records any value during the program.
By forward saying, we can know there isn't any matrix operating during the implement.
Instead of that, it declares every neuron really within the program.
So we can use it to analyze the neural net.
<br/>
<br/>

## How we start

#### Include the header.

```C++
#include <EasyNerual.h>
```

#### Get a manager.

```C++
neuralManager net;
```

It's just that easy to get the `neuralManager`. 
Let's us discuss how to config or manager the net by `neuralManager`.

### Config Net

+ Firstly, add `neural` in `neuralManager`.
+ Secondly, make connect and set weight between two `neural`.
+ Thirdly, make signal source. 

#### Add Neural 

There is a thing that you have to know it first. 
The `neural` is construct by two function point. 
They are defined as following.
```C++
typedef Signal(*judge)(double,unsigned int);
typedef double(*countor)(vector<Signal>, vector<Weight>);
```
The `judge` is transfer function in `neural`. 
And the `countor` is sum function in `neural`. 
So if you want to get `neural`, you need to get these two function point first.<br/><br/>
_Note:We already write some functions for both `judge` and `countor` in `neuronFun.h`._

```C++
neural(countor countFunction,judge judgeFunction);
//neural construct function~~
```

Here are three ways to add `neural` in `neuralManager`. 
```C++
void 		 neuralManager::addNeural(countor initc ,judge initj ,unsigned int* ID);
```
These parameters are `judge` to init, `countor` to init, neural id, respectively.<br/>

```C++
unsigned int neuralManager::addNeural(countor initc ,judge initj);
```

This way just like previous one, but the neural id will be returned.<br/>

```C++
unsigned int neuralManager::addNeural(neural pushed);
```
If you have already had a `neural`, you can use this way.<br/>

#### Connection and Weight

We have added `neural` in and got the id. 
Next, we can use the id to connect them and set up the weight by the function.

```C++
void neuralManager::makeConnect(unsigned int source, unsigned int target, double weightVal);
```
This function can connect *source* to *target* and set up the weight between *source* and *target*.

#### Signal Point & End Point

After neural net architecture have finished. 
We can send the signal to the net, but we don't that where to send the signal. 
So we need to make a *signal point* to send the signal. 
Some function can do that here.

```C++
unsigned int neuralManager::makeSP();
void		 neuralManager::makeEP(unsigned int endPoint);
void		 neuralManager::addEntrance(unsigned int mark);
void		 neuralManager::pushSignalIn(Signal In, unsigned int mark);
```
There are three functions. 
Let's us discuss how to use them. <br/>
The `makeSP()` make a *signal point* and return neural id which allows us control *signal point*. <br/>
The `makeEP(unsigned int)` set a *end point* for the net. <br/>
The `addEntrance(unsigned int)` make `neuralManager` know where to start in the net. <br/>
The `pushSignalIn(Signal,unsigned int)` can send the signal to *signal point*. 
The second parameter is that where you want to send the signal.<br/>

#### Active and Get output

How to active the net? 
It's easy. Just `active`.
```C++
void   neuralManager::active();
```
Next, if you want to get any output of any neuron, you can use the function.
```C++
Signal neuralManager::getOutputVal(unsigned int forcus);
```
The parameter which called *forcus* is the id of output neuron.

# Sample Code
The sample code is an and gate. 
You can find it in the *sample* directory.
```C++
#include "neuralManager.h"
#include <iostream>

using namespace std;

typedef Signal(*judge)(double,unsigned int);
typedef double(*countor)(vector<Signal>, vector<Weight>);

Signal jud(double in,unsigned int mark)
{
	Signal returnVal;
	returnVal.SignalOrigin = mark;

	returnVal.value = in==2?1:0;

	return returnVal;
}

double cou(vector<Signal> signalIn,vector<Weight> weight)
{
	double sum = 0.0;

	for(auto i:signalIn)
		sum += i.value;

	return sum;
}

int main(void)
{
	judge   initj = jud;
	countor initc = cou;
	neuralManager net;

	double val;
	Signal signal;
	signal.SignalOrigin = static_cast<unsigned int>(TypeOfSignalEnd::SIGNALPOINT) ;

	unsigned int n1_mark   = net.addNeural(initc, initj);
	unsigned int signalin1 = net.makeSP();
	unsigned int signalin2 = net.makeSP();

	net.makeConnect(signalin1,n1_mark,1);
	net.makeConnect(signalin2,n1_mark,1);
	net.makeEP(n1_mark);
	
	net.addEntrance(signalin1);
	net.addEntrance(signalin2);

	cout << "Input the first Signal:";
	cin >> val;
	signal.value = val;
	net.pushSignalIn(signal, signalin1);

	cout << "Input the second Signal:";
	cin >> val;
	signal.value = val;
	net.pushSignalIn(signal, signalin2);

	net.active();
	cout << "Output: " << net.getOutputVal(n1_mark).value << endl;

	return 0;
}
```
<br/>
# Contributing
1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: ` git push origin my-new-feature`
5. Submit a pull request :D

