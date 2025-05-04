from core.bdd import BDD

expr = (1, (2, False, True), (3, True, (4, False, True)))  # Represents x1 ? (x2 ? False : True) : (x3 ? True : False)
bdd = BDD.build_from_expr(expr)

tt = "1100100100001111"
bdd = BDD.build_from_truth_table(tt)
bdd.display()