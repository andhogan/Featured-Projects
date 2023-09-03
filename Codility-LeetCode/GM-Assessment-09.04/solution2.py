# you can write to stdout for debugging purposes, e.g.
# print("this is a debug message")

def solution(S):
    # Intialize player coordinates
    successes = 0
    length = len(S)
    player_pos = {'P'+str(n): [n, 0] for n in range(length)}
    #print(player_pos)

    
    # iterate through string directions
    for i in range(length):
        curr_player = 'P'+str(i)
        curr_position = list(player_pos[curr_player]) # player's current position (value)
        move = S[i] # player's current move

        # Debugging...
        #print("CURR_PLAYER: "+curr_player)
        #print("CURR_POSITION: ")
        #print(curr_position)
        #print("MOVE: " + move)

        # Update player direction, check whether two players occupy same tile

        # Leftmost player at start can move anywhere but right
        if i == 0:  
            if move != '>':
                successes += 1
                #print("X:"+str(curr_position[0])) # Debugging...
                #print("Y:"+str(curr_position[1]))
                player_pos[curr_player][0] -= 1
                #print("New Position: ")
                #print(curr_position)
                #player_pos[curr_player] = curr_position
                continue

        # Up and Down are always successful
        if move == "^":
            successes += 1
            curr_position[1] += 1
            player_pos[curr_player] = curr_position

        if move == "v":
            successes += 1
            curr_position[1] -= 1
            player_pos[curr_player] = curr_position

        # Left and Right require checks on previous player positions
        # Check to see if two positions are in the list of values
            # If it is, player fails to move and does not change position
            # If not, player moves and update player direction

        if move == "<":
            curr_position[0] -= 1
            if curr_position in player_pos.values():
                continue
            else: # add success, change player position
                successes += 1
                player_pos[curr_player] = curr_position

        if move == ">":
            curr_position[0] += 1
            if curr_position in player_pos.values(): # if position is found in values, fail
                continue
            else: # add success, change player position
                successes += 1
                player_pos[curr_player] = curr_position

        

    return successes

print(f"solution('><^v') = {solution('><^v')}. It is {'correct' if solution('><^v') == 2 else 'wrong' }.")
print(f"solution('<<^<v>>') = {solution('<<^<v>>')}. It is {'correct' if solution('<<^<v>>') == 6 else 'wrong' }.")
print(f"solution('><><') = {solution('><><')}. It is {'correct' if solution('><><') == 0 else 'wrong' }.")
    

