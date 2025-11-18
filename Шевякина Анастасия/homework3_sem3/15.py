import heapq
from collections import deque

def is_solvable(board):
    size = len(board)
    tiles = []
    blank_row_from_bottom = 0
    
    for i in range(size):
        for j in range(size):
            if board[i][j] == 0:
                blank_row_from_bottom = size - i 
            else:
                tiles.append(board[i][j])
    
    inversions = 0
    n = len(tiles)
    for i in range(n):
        for j in range(i + 1, n):
            if tiles[i] > tiles[j]:
                inversions += 1
    
    print(f"Инверсии: {inversions}, Строка пустой снизу: {blank_row_from_bottom}")
    print(f"Формула: ({inversions} + {blank_row_from_bottom}) % 2 = {(inversions + blank_row_from_bottom) % 2}")
    if size % 2 == 1:
        return inversions % 2 == 0
    else:
        return (inversions + blank_row_from_bottom) % 2 == 1

def manhattan_distance(board, goal_positions):
    distance = 0
    for i in range(4):
        for j in range(4):
            value = board[i][j]
            if value != 0:
                target_i, target_j = goal_positions[value]
                distance += abs(i - target_i) + abs(j - target_j)
    return distance

def misplaced_tiles(board, goal):
    count = 0
    for i in range(4):
        for j in range(4):
            if board[i][j] != 0 and board[i][j] != goal[i][j]:
                count += 1
    return count

def get_neighbors(board):
    neighbors = []

    empty_i, empty_j = -1, -1
    for i in range(4):
        for j in range(4):
            if board[i][j] == 0:
                empty_i, empty_j = i, j
                break
        if empty_i != -1:
            break
    
    directions = [(-1, 0, 'UP'), (1, 0, 'DOWN'), 
                  (0, -1, 'LEFT'), (0, 1, 'RIGHT')]
    
    for di, dj, move in directions:
        new_i, new_j = empty_i + di, empty_j + dj
        
        if 0 <= new_i < 4 and 0 <= new_j < 4:
            new_board = [row[:] for row in board]
            new_board[empty_i][empty_j], new_board[new_i][new_j] = \
                new_board[new_i][new_j], new_board[empty_i][empty_j]
            neighbors.append((new_board, move))
    
    return neighbors

def board_to_string(board):
    return ''.join(str(cell) for row in board for cell in row)

def solve_astar(start, goal):
    if start == goal:
        return []
    
    goal_positions = {}
    for i in range(4):
        for j in range(4):
            goal_positions[goal[i][j]] = (i, j)
    
    open_set = []
    start_g = 0
    start_h = manhattan_distance(start, goal_positions)
    start_f = start_g + start_h
    
    heapq.heappush(open_set, (start_f, start_g, start, []))
    
    best_costs = {board_to_string(start): start_g}
    
    while open_set:
        current_f, current_g, current_board, current_path = heapq.heappop(open_set)
        
        current_key = board_to_string(current_board)
        if best_costs.get(current_key, float('inf')) < current_g:
            continue
            
        if current_board == goal:
            return current_path
        
        for neighbor_board, move in get_neighbors(current_board):
            neighbor_g = current_g + 1
            neighbor_key = board_to_string(neighbor_board)
            
            if neighbor_key not in best_costs or neighbor_g < best_costs[neighbor_key]:
                best_costs[neighbor_key] = neighbor_g
                neighbor_h = manhattan_distance(neighbor_board, goal_positions)
                neighbor_f = neighbor_g + neighbor_h
                neighbor_path = current_path + [move]
                
                heapq.heappush(open_set, (neighbor_f, neighbor_g, neighbor_board, neighbor_path))
    
    return []

def read_board():
    board = []
    print("Введите начальное состояние доски (4 строки по 4 числа):")
    for _ in range(4):
        row = []
        tokens = input().split()
        for token in tokens:
            if token.startswith('0') and len(token) == 2:
                token = token[1]
            row.append(int(token))
        board.append(row)
    return board

def main():
    goal = [
        [1, 2, 3, 4],
        [5, 6, 7, 8],
        [9, 10, 11, 12],
        [13, 14, 15, 0]
    ]
    start=read_board()
    if start==goal:
        print("Головоломка уже решена!")
        return
    if not is_solvable(start):
        print("Решить невозможно!")
        return
    print("Поиск решения с помощью A*...")
    solution = solve_astar(start, goal)
    if not solution:
        print("Решение не найдено!")
    else:
        print(f"Решение найдено! Ходов: {len(solution)}")
        print("Последовательность:", " ".join(solution))
    print('\n')

if __name__ == "__main__":
    main()