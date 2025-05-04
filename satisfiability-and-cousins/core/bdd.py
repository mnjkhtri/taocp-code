class BDDNode:
    def __init__(self, val=None, low=None, high=None):
        self.val = val
        self.low = low
        self.high = high

    def __str__(self):
        low = self.low if isinstance(self.low, bool) else f"{self.low.val}"
        high = self.high if isinstance(self.low, bool) else f"{self.high.val}"
        return f"VAL: {self.val}, LOW: {low}, HIGH: {high}"

class BDD:
    def __init__(self, truth_table = None):
        self.root = None
        self.truth_table = truth_table

        self.beads = set()

    @property
    def num_beads(self): return len(self.beads)

    @property
    def num_solutions(self): return sum(1 for t in self.truth_table if t == '1')

    @classmethod
    def build_from_expr(cls, expr):
        """
        Build the BDD from a Boolean expression and return a new BDD instance.
        
        Parameters:
        expr (tuple): A Boolean expression represented as a nested tuple. 
                      The tuple should have the structure (idx, low_expr, high_expr), 
                      where idx is the variable index, low_expr is the expression for the False branch, 
                      and high_expr is the expression for the True branch.
                      Boolean literals (True, False) can be used as terminal expressions.

        Example:
        To build a BDD for the expression x1 ? (x2 ? False : True) : (x3 ? True : False), use:
        expr = (1, (2, False, True), (3, True, False))
        
        Returns:
        BDD: A new instance of BDD with the expression built.
        """
        def build_expr(expr):
            if isinstance(expr, bool): return expr
            idx, low_expr, high_expr = expr
            return BDDNode(idx, build_expr(low_expr), build_expr(high_expr))
    
        bdd = cls()
        bdd.root = build_expr(expr)
        return bdd
    
    @classmethod
    def build_from_truth_table(cls, truth_table):
        """
        Build the BDD from a truth table and return a new BDD instance.
        
        Parameters:
        truth_table (str): A binary string representing the truth table in lexicographical order.
        
        Returns:
        BDD: A new instance of BDD with the truth table built.

        Raises:
        ValueError: If the length of the truth table is not a power of two.
        """
        if len(truth_table) & (len(truth_table) - 1) != 0:
            raise ValueError("The length of the truth table must be a power of two.")

        bdd = cls(truth_table)

        memo = {}
        def build_subtable(idx, subtable):
            if all(c == '0' for c in subtable): return False
            if all(c == '1' for c in subtable): return True
            mid = len(subtable) // 2
            if subtable[:mid] == subtable[mid:]:
                return build_subtable(idx+1, subtable[:mid])
            if subtable not in memo: 
                node = BDDNode(idx, build_subtable(idx+1, subtable[:mid]), build_subtable(idx+1, subtable[mid:]))
                bdd.beads.add(subtable)
                memo[subtable] = node
            return memo[subtable]

        bdd.root = build_subtable(1, truth_table)
        return bdd
    
    def display(self, node=None, indent=0):
        """
        Display the BDD in a human-readable form.
        """
        if node is None:
            node = self.root
        if isinstance(node, bool):
            print("  " * indent + str(node))
        else:
            print("  " * indent + "x" + str(node.val))
            self.display(node.low, indent + 1)
            self.display(node.high, indent + 1)