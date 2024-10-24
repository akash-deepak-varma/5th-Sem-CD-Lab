class Production:
    def __init__(self, lhs, rhs):
        self.lhs = lhs
        self.rhs = rhs

    def __str__(self):
        return f"{self.lhs} -> {' '.join(self.rhs)}"


class LR0Item:
    def __init__(self, production, dot_position):
        self.production = production
        self.dot_position = dot_position

    def __str__(self):
        lhs = self.production.lhs
        rhs = self.production.rhs
        return f"{lhs} -> {' '.join(rhs[:self.dot_position])} . {' '.join(rhs[self.dot_position:])}"


class State:
    def __init__(self):
        self.items = set()

    def add_item(self, item):
        self.items.add(item)

    def closure(self, productions):
        changed = True
        while changed:
            changed = False
            for item in list(self.items):
                if item.dot_position < len(item.production.rhs):
                    next_symbol = item.production.rhs[item.dot_position]
                    for prod in productions:
                        if prod.lhs == next_symbol:
                            new_item = LR0Item(prod, 0)
                            if new_item not in self.items:
                                self.add_item(new_item)
                                changed = True

    def __str__(self):
        return "\n".join(str(item) for item in self.items)


class LALRParser:
    def __init__(self, productions):
        self.productions = productions
        self.states = []
        self.action_table = {}
        self.goto_table = {}
        self.start_symbol = productions[0].lhs

    def build_table(self):
        initial_state = State()
        initial_item = LR0Item(self.productions[0], 0)
        initial_state.add_item(initial_item)
        initial_state.closure(self.productions)

        self.states.append(initial_state)

        for state in self.states:
            self.compute_goto(state)

        self.define_tables()

    def compute_goto(self, state):
        for item in state.items:
            if item.dot_position < len(item.production.rhs):
                symbol = item.production.rhs[item.dot_position]
                new_item = LR0Item(item.production, item.dot_position + 1)
                new_state = State()
                new_state.add_item(new_item)
                new_state.closure(self.productions)

                if new_state not in self.states:
                    self.states.append(new_state)

                self.action_table[(state, symbol)] = 'SHIFT'
                self.goto_table[(state, symbol)] = new_state

    def define_tables(self):
        for i, state in enumerate(self.states):
            for item in state.items:
                if item.dot_position == len(item.production.rhs):
                    if item.production.lhs == self.start_symbol:
                        self.action_table[(state, '$')] = 'ACCEPT'
                    else:
                        self.action_table[(state, '$')] = 'REDUCE'

    def parse(self, input_string):
        stack = [0]
        input_string += '$'
        index = 0

        while True:
            state = stack[-1]
            symbol = input_string[index]

            action = self.action_table.get((state, symbol))

            if action == 'SHIFT':
                stack.append(self.goto_table[(state, symbol)])
                index += 1
            elif action == 'REDUCE':
                production = self.productions[0]  # Placeholder for reduced production
                for _ in production.rhs:  # Pop for RHS length
                    stack.pop()
                stack.append(self.goto_table.get((stack[-1], production.lhs)))
            elif action == 'ACCEPT':
                print("Input accepted!")
                return True
            else:
                print("Parse error!")
                return False


def input_grammar():
    productions = []
    print("Enter grammar productions (e.g., S -> A B), one per line.")
    print("Type 'END' when you are finished:")
    
    while True:
        line = input().strip()
        if line == "END":
            break
        lhs, rhs = line.split('->')
        lhs = lhs.strip()
        rhs = rhs.strip().split()
        productions.append(Production(lhs, rhs))
    
    return productions


def main():
    productions = input_grammar()
    parser = LALRParser(productions)
    parser.build_table()

    input_string = input("Enter a string to parse (e.g., 'ab'): ")
    parser.parse(input_string)


if __name__ == "__main__":
    main()
