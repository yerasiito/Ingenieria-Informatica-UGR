def unbounded_knapsack_dp_tabulation(weights, profits, capacity):
    n = len(profits)
    table = [[0] * (capacity + 1) for i in range(n)]

    # When capacity is 0, none of the item can be selected
    for i in range(n):
        table[i][0] = 0

    # When only 1 item is considered, get the profits using that item for every capapcity 'c'
    for c in range(capacity + 1):
        table[0][c] = (c // weights[0]) * profits[0]

    # For each item, check for every possible capacities
    for i in range(1, n):
        for c in range(1, capacity + 1):
            if (weights[i] <= c):
                table[i][c] = max(table[i - 1][c], profits[i] + table[i][c - weights[i]])
            else:
                table[i][c] = table[i - 1][c]


    pick_selected_items(table, weights, profits)

    return table[i][c]


def pick_selected_items(table, weights, profits):
    i, c = len(table)-1, len(table[0])-1
    total_profit = table[i][c]

    print("Selected items are : ")
    while (i-1 >= 0 and table[i][c] >= 0):
        if (table[i][c] != table[i - 1][c]):
            print(f"item - {i+1} with weight : {weights[i]} and profit : {profits[i]}")
            c -= weights[i]
            total_profit -= profits[i]
        else:
            i -= 1

    while (total_profit > 0):
        print(f"item - {1} with weight : {weights[0]} and profit : {profits[0]}")
        total_profit -= profits[0]


print("\nDP -> Iteration + Tabulation Method :")
print(unbounded_knapsack_dp_tabulation([3, 4, 6], [7,8,11], 10))
