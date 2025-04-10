class Solution:
    def merge(self, lhs, rhs):
        result = []
        i = j = 0

        while len(result) < len(rhs)+len(lhs) and i<len(lhs) and j<len(rhs):
            if (lhs[i] < rhs[j]):
                result.append(lhs[i])
                i+=1
            else:
                result.append(rhs[j])
                j+=1
        if i < len(lhs):
            result += lhs[i:]
        if j < len(rhs):
            result += rhs[j:]
        return result


    def merge_sort(self, a):
        if len(a)<=1:
            return a
        mid = len(a) // 2
        left = self.merge_sort(a[:mid])
        right = self.merge_sort(a[mid:])
        return self.merge(left, right)
    def sortArray(self, nums: list[int]) -> list[int]:
        nums = self.merge_sort(nums)
        return nums
        

