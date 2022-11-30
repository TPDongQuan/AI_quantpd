import turtle
import random
import time
global move_history
def make_empty_board(sz):
    board = []
    for i in range (sz):
        board.append ([" "] * sz)
    return board
def is_empty(board):
    return board == [[' '] * len (board)] * len (board)
def is_in(board, y, x):
    return 0 <= y < len (board) and 0 <= x < len (board)
def is_win(board):
    black = score_of_col (board, 'b')
    white = score_of_col (board, 'w')
    sum_sumcol_values (black)
    sum_sumcol_values (white)
    if 5 in black and black[5] == 1:
        return 'Black won'
    elif 5 in white and white[5] == 1:
        return 'White won'
    if sum (black.values ( )) == black[-1] and sum (white.values ( )) == white[-1] or possible_moves (board) == []:
        return 'Draw'
    return 'Continue playing'
def march(board, y, x, dy, dx, length):
    '''
    t�m v? tr� xa nh?t trong dy,dx trong kho?ng length
    '''
    yf = y + length * dy
    xf = x + length * dx
    while not is_in (board, yf, xf):
        yf -= dy
        xf -= dx
    return yf, xf
def score_ready(scorecol):
    sumcol = {0: {}, 1: {}, 2: {}, 3: {}, 4: {}, 5: {}, -1: {}}
    for key in scorecol:
        for score in scorecol[key]:
            if key in sumcol[score]:
                sumcol[score][key] += 1
            else:
                sumcol[score][key] = 1
    return sumcol
def sum_sumcol_values(sumcol):
    for key in sumcol:
        if key == 5:
            sumcol[5] = int (1 in sumcol[5].values ( ))
        else:
            sumcol[key] = sum (sumcol[key].values ( ))
def score_of_list(lis, col):
    blank = lis.count (' ')
    filled = lis.count (col)

    if blank + filled < 5:
        return -1
    elif blank == 5:
        return 0
    else:
        return filled
def row_to_list(board, y, x, dy, dx, yf, xf):
    row = []
    while y != yf + dy or x != xf + dx:
        row.append (board[y][x])
        y += dy
        x += dx
    return row
def score_of_row(board, cordi, dy, dx, cordf, col):
    colscores = []
    y, x = cordi
    yf, xf = cordf
    row = row_to_list (board, y, x, dy, dx, yf, xf)
    for start in range (len (row) - 4):
        score = score_of_list (row[start:start + 5], col)
        colscores.append (score)
    return colscores
def score_of_col(board, col):
    f = len (board)
    scores = {(0, 1): [], (-1, 1): [], (1, 0): [], (1, 1): []}
    for start in range (len (board)):
        scores[(0, 1)].extend (score_of_row (board, (start, 0), 0, 1, (start, f - 1), col))
        scores[(1, 0)].extend (score_of_row (board, (0, start), 1, 0, (f - 1, start), col))
        scores[(1, 1)].extend (score_of_row (board, (start, 0), 1, 1, (f - 1, f - 1 - start), col))
        scores[(-1, 1)].extend (score_of_row (board, (start, 0), -1, 1, (0, start), col))

        if start + 1 < len (board):
            scores[(1, 1)].extend (score_of_row (board, (0, start + 1), 1, 1, (f - 2 - start, f - 1), col))
            scores[(-1, 1)].extend (score_of_row (board, (f - 1, start + 1), -1, 1, (start + 1, f - 1), col))
    return score_ready (scores)
def score_of_col_one(board, col, y, x):
    scores = {(0, 1): [], (-1, 1): [], (1, 0): [], (1, 1): []}

    scores[(0, 1)].extend (score_of_row (board, march (board, y, x, 0, -1, 4), 0, 1, march (board, y, x, 0, 1, 4), col))

    scores[(1, 0)].extend (score_of_row (board, march (board, y, x, -1, 0, 4), 1, 0, march (board, y, x, 1, 0, 4), col))

    scores[(1, 1)].extend (
        score_of_row (board, march (board, y, x, -1, -1, 4), 1, 1, march (board, y, x, 1, 1, 4), col))

    scores[(-1, 1)].extend (
        score_of_row (board, march (board, y, x, -1, 1, 4), 1, -1, march (board, y, x, 1, -1, 4), col))
    return score_ready (scores)
def possible_moves(board):
    taken = []
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0), (1, 1), (-1, -1), (-1, 1), (1, -1)]
    cord = {}
    for i in range (len (board)):
        for j in range (len (board)):
            if board[i][j] != ' ':
                taken.append ((i, j))
    for direction in directions:
        dy, dx = direction
        for coord in taken:
            y, x = coord
            for length in [1, 2, 3, 4]:
                move = march (board, y, x, dy, dx, length)
                if move not in taken and move not in cord:
                    cord[move] = False
    return cord
def TF34score(score3, score4):
    for key4 in score4:
        if score4[key4] >= 1:
            for key3 in score3:
                if key3 != key4 and score3[key3] >= 2:
                    return True
    return False
def stupid_score(board, col, anticol, y, x):
    global colors
    M = 1000
    res, adv, dis = 0, 0, 0

    board[y][x] = col
    sumcol = score_of_col_one (board, col, y, x)
    a = winning_situation (sumcol)
    adv += a * M
    sum_sumcol_values (sumcol)
    adv += sumcol[-1] + sumcol[1] + 4 * sumcol[2] + 8 * sumcol[3] + 16 * sumcol[4]

    board[y][x] = anticol
    sumanticol = score_of_col_one (board, anticol, y, x)
    d = winning_situation (sumanticol)
    dis += d * (M - 100)
    sum_sumcol_values (sumanticol)
    dis += sumanticol[-1] + sumanticol[1] + 4 * sumanticol[2] + 8 * sumanticol[3] + 16 * sumanticol[4]

    res = adv + dis

    board[y][x] = ' '
    return res
def winning_situation(sumcol):
    '''
    tr? l?i t�nh hu?ng chi?n th?ng d?ng nhu:
    {0: {}, 1: {(0, 1): 4, (-1, 1): 3, (1, 0): 4, (1, 1): 4}, 2: {}, 3: {}, 4: {}, 5: {}, -1: {}}
    1-5 luu di?m c� d? nguy hi?m t? th?p d?n cao,
    -1 l� roi v�o tr?ng th�i t?i, c?n ph�ng th?
    '''
    if 1 in sumcol[5].values ( ):
        return 5
    elif len (sumcol[4]) >= 2 or (len (sumcol[4]) >= 1 and max (sumcol[4].values ( )) >= 2):
        return 4
    elif TF34score (sumcol[3], sumcol[4]):
        return 4
    else:
        score3 = sorted (sumcol[3].values ( ), reverse=True)
        if len (score3) >= 2 and score3[0] >= score3[1] >= 2:
            return 3
    return 0
def best_move(board, col):
    '''
    tr? l?i di?m s? c?a m?ng trong l?i th? c?a t?ng m�u
    '''
    if col == 'w':
        anticol = 'b'
    else:
        anticol = 'w'

    movecol = (0, 0)
    maxscorecol = ''
    if is_empty (board):
        movecol = (int ((len (board)) * random.random ( )), int ((len (board[0])) * random.random ( )))
    else:
        moves = possible_moves (board)

        for move in moves:
            y, x = move
            if maxscorecol == '':
                scorecol = stupid_score (board, col, anticol, y, x)
                maxscorecol = scorecol
                movecol = move
            else:
                scorecol = stupid_score (board, col, anticol, y, x)
                if scorecol > maxscorecol:
                    maxscorecol = scorecol
                    movecol = move
    return movecol
def click(x, y):
    global board, colors, win, move_history

    x, y = getindexposition (x, y)

    if x == -1 and y == -1 and len (move_history) != 0:
        x, y = move_history[-1]

        del (move_history[-1])
        board[y][x] = " "
        x, y = move_history[-1]

        del (move_history[-1])
        board[y][x] = " "
        return

    if not is_in (board, y, x):
        return

    if board[y][x] == ' ':

        draw_stone (x, y, colors['b'])
        board[y][x] = 'b'

        move_history.append ((x, y))

        game_res = is_win (board)
        if game_res in ["White won", "Black won", "Draw"]:
            print (game_res)
            win = True
            return

        ay, ax = best_move (board, 'w')
        draw_stone (ax, ay, colors['w'])
        board[ay][ax] = 'w'

        move_history.append ((ax, ay))

        game_res = is_win (board)
        if game_res in ["White won", "Black won", "Draw"]:
            print (game_res)
            win = True
            return


def initialize(size):
    global win, board, screen, colors, move_history

    move_history = []
    win = False
    board = make_empty_board (size)

    screen = turtle.Screen ( )
    screen.onclick (click)
    screen.setup (screen.screensize ( )[1] * 2, screen.screensize ( )[1] * 2)
    screen.setworldcoordinates (-1, size, size, -1)
    screen.bgcolor ('orange')
    screen.tracer (500)

    colors = {'w': turtle.Turtle ( ), 'b': turtle.Turtle ( ), 'g': turtle.Turtle ( )}
    colors['w'].color ('white')
    colors['b'].color ('black')

    for key in colors:
        colors[key].ht ( )
        colors[key].penup ( )
        colors[key].speed (0)

    border = turtle.Turtle ( )
    border.speed (9)
    border.penup ( )

    side = (size - 1) / 2

    i = -1
    for start in range (size):
        border.goto (start, side + side * i)
        border.pendown ( )
        i *= -1
        border.goto (start, side + side * i)
        border.penup ( )

    i = 1
    for start in range (size):
        border.goto (side + side * i, start)
        border.pendown ( )
        i *= -1
        border.goto (side + side * i, start)
        border.penup ( )
    border.ht ( )
    screen.listen ( )
    screen.mainloop ( )
def getindexposition(x, y):
    '''
    l?y index
    '''
    intx, inty = int (x), int (y)
    dx, dy = x - intx, y - inty
    if dx > 0.5:
        x = intx + 1
    elif dx < -0.5:
        x = intx - 1
    else:
        x = intx
    if dy > 0.5:
        y = inty + 1
    elif dx < -0.5:
        y = inty - 1
    else:
        y = inty
    return x, y
def draw_stone(a, b, colturtle):
    colturtle.goto (a, b - 0.5)
    colturtle.pendown ( )
    colturtle.begin_fill ( )
    colturtle.circle (0.5)
    colturtle.end_fill ( )
    colturtle.penup ( )
if __name__ == '__main__':
    initialize (20)
