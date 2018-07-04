# AVL-Tree ![CI status](https://img.shields.io/badge/build-passing-brightgreen.svg)

AVL tree implementation in C++.
Done as part of Data Structures course in IIT.

## Usage

```c++
include <TreeAVL.h>

class CompareByHeight {
	public:
		int operator()(Person& p1, Person& p2) {
			int h1 = p1.getHeight();
			int h2 = p2.getHeight();
			return (h1 - h2);
		}
};
mytree = Tree<CompareByID, Person>)();
myTree.insertVertex(new Person(...))

```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)