# Defines a Jar class, representing a cookie jar and its attributes


# Test Jar class
def main():
    jar = Jar(5)

    jar.deposit(3)
    print(str(jar))

    jar.withdraw(2)
    print(str(jar))


# Definition of Jar class
class Jar:
    # Initialization method, capacity 12 if no parameter given
    def __init__(self, capacity=12):
        self.capacity = capacity
        self._size = 0

    # Return a string of amount of cookies in jar
    def __str__(self):
        return "🍪" * self.size

    # Deposit, or add, n cookies in jar, with check if there is enough capacity
    def deposit(self, n):
        if self.size + n > self.capacity:
            raise ValueError("Invalid deposit")
        self._size += n

    # Withdraw, or subtract, n cookies from jar, with check if there are enough
    def withdraw(self, n):
        if n > self.size:
            raise ValueError("Invalid withdraw")
        self._size -= n

    # capacity getter
    @property
    def capacity(self):
        return self._capacity

    # capacity setter, check if parameter negative, thus invalid
    @capacity.setter
    def capacity(self, capacity):
        if capacity < 0:
            raise ValueError("Invalid capacity")
        self._capacity = capacity

    # size getter
    @property
    def size(self):
        return self._size


main()
