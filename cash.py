from cs50 import get_float


def main():
    getchange()


def getchange():
    change = get_float("How much change do you need? ")
    if change < 0:
        getchange()
    else:
        change = change*100
        q = int(change / 25)
        change = change - (q*25)
        d = int(change / 10)
        change = change - (d*10)
        n = int(change / 5)
        change = change - (n*5)
        p = int(change / 1)
        change = change - (p*1)
        coins = int(q+d+n+p)
        print(coins)


main()
