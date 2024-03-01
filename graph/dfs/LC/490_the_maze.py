# https://leetcode.com/problems/the-maze/
from typing import List
class Solution:
    def hasPath(
        self, maze: List[List[int]], start: List[int], destination: List[int]
    ) -> bool:
        """
        Using DFS can solve this problem.
        time complexity: O(m*n)
        space complexity: O(m*n)
        """
        open_list = [tuple(start)]
        R, C = len(maze), len(maze[0])
        visited = [[False] * C for _ in range(R)]
        while open_list:
            i, j = open_list.pop()
            if [i, j] == destination:
                return True
            for di, dj in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                r, c = i, j
                while 0 <= r < R and 0 <= c < C and maze[r][c] == 0:
                    r += di
                    c += dj
                r -= di
                c -= dj
                if visited[r][c]:
                    continue
                visited[r][c] = True
                open_list.append((r, c))
        return False


"""
Takeaways:
This is kind of a standard DFS algorithm with a twist. The twist is that we need to keep
moving in a direction until we hit a wall.
"""

if __name__ == "__main__":
    maze = [
        [0, 0, 1, 0, 0],
        [0, 0, 0, 0, 0],
        [0, 0, 0, 1, 0],
        [1, 1, 0, 1, 1],
        [0, 0, 0, 0, 0],
    ]
    start = [0, 4]
    destination = [4, 4]
    maze = [
        [0, 0, 1, 0, 0],
        [0, 0, 0, 0, 0],
        [0, 0, 0, 1, 0],
        [1, 1, 0, 1, 1],
        [0, 0, 0, 0, 0],
    ]
    start = [0, 4]
    destination = [3, 2]
    sol = Solution()
    print(sol.hasPath(maze, start, destination))
