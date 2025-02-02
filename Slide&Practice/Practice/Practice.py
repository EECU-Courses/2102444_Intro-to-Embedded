# list = [1,2,3,4,5,6,7]
# print(list.pop())
# list.append(11)
# print(list.pop())

class addition:
    def __init__(self, **arg):
        self.x = 1
        self.y = 2

    def __call__(self):
        return self.x + self.y
    
    def _print(self):
        print(self._z)
    
    _z = 10

x = addition()
x._print()