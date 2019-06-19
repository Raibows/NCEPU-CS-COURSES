class vector:
    def __init__(self, x=0, y=0, z=0):
        self.x = x
        self.y = y
        self.z = z
    def __add__(self, other):
        temp = vector()
        temp.x = self.x + other.x
        temp.y = self.y + other.y
        temp.z = self.z + other.z
        return temp
    def __sub__(self, other):
        temp = vector()
        temp.x = self.x - other.x
        temp.y = self.y - other.y
        temp.z = self.z - other.z
        return temp
    def __mul__(self, other):
        temp = vector()
        temp.x = self.x * other
        temp.y = self.y * other
        temp.z = self.z * other
        return temp
    def __truediv__(self, other):
        temp = vector()
        temp.x = self.x / other
        temp.y = self.y / other
        temp.z = self.z / other
        return temp
    def __repr__(self):
        return '{} {} {}'.format(self.x, self.y, self.z)

x1 = vector(1,2,3)
x2 = vector(3,2,1)
print(x2+x1)
print(x2-x1)
print(x1 * 3)
print(x2 / 2)
