class Data:
    def __init__(self, day, month, year):
        self.day = int(day)
        self.month = int(month)
        self.year = int(year)

    def __lt__(self, rhs):
        if self.year == rhs.year:
            if self.month == rhs.month:
                return self.day < rhs.day
            return self.month < rhs.month
        return self.year < rhs.year

    def __repr__(self):
        return f" day :{self.day} month :{self.month} year:{self.year}"


class Person:
    def __init__(self, born: Data, died: Data):
        self.birth = born
        self.death = died
        self.__months_length = {
            1: 31,
            2: 28,
            3: 31,
            4: 30,
            5: 31,
            6: 30,
            7: 31,
            8: 31,
            9: 30,
            10: 31,
            11: 30,
            12: 31
        }
        if self.birth.year % 4 == 0:
            self.__months_length[2] = 29
        else:
            self.__months_length[2] = 28

    def when_start(self):
        new_day = self.birth.day
        new_month = self.birth.month
        new_year = self.birth.year + 18
        return Data(new_day, new_month, new_year)

    def when_end(self):
        new_day = self.birth.day - 1
        new_month = self.birth.month
        new_year = self.birth.year + 80
        if new_day == 0:
            if new_month == 1:
                new_year -= 1
                new_month = 12
            else:
                new_month -= 1
            new_day = self.__months_length[new_month]
        age_80 = Data(new_day, new_month, new_year)
        if self.death < age_80:
            if self.death.day == 1:
                if self.death.month == 1:
                    self.death.year -= 1
                    self.death.month = 12
                    self.death.day = 31
                else:
                    self.death.day = self.__months_length[self.death.month - 1]
                    self.death.month -= 1
            else:
                self.death.day -= 1
            return self.death
        else:
            return age_80


n = int(input())
people = []
for i in range(n):
    s = input().split()
    person = Person(Data(s[0], s[1], s[2]), Data(s[3], s[4], s[5]))
    data1, data2 = person.when_start(), person.when_end()
    people.append((data1, data2))

people.sort()
start = people[0][0]
stop = people[0][1]
k = 0
max_k = 0
for i in range(len(people)):
    if people[i][0] < stop:
        k += 1
        print(f"{people[i][0]=}, {stop=}")
    else:
        start = people[i][0]
        stop = people[i][1]
        k -= 1
    max_k = max(max_k, k)

print(max_k)
