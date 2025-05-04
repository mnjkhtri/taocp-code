import unittest
from core.bdd import BDD

class TestBDD(unittest.TestCase):
    def test_truth_table_all_zeros(self):
        truth_table = "0000"
        bdd = BDD.build_from_truth_table(truth_table)
        self.assertEqual(bdd.num_beads, 0)  # Only terminal node
        self.assertEqual(bdd.root, False)

    def test_truth_table_all_ones(self):
        truth_table = "1111"
        bdd = BDD.build_from_truth_table(truth_table)
        self.assertEqual(bdd.num_beads, 0)  # Only terminal node
        self.assertEqual(bdd.root, True)

    def test_truth_table_reduced(self):
        truth_table = "01011111"
        bdd = BDD.build_from_truth_table(truth_table)
        self.assertEqual(bdd.num_beads, 2)  # Check the number of non-terminal nodes

    def test_truth_table_minimalist(self):
        truth_table = "01010101"
        bdd = BDD.build_from_truth_table(truth_table)
        self.assertEqual(bdd.num_beads, 1)  # Check the number of non-terminal nodes

    def test_truth_table_mixed(self):
        truth_table = "1100100100001111"
        bdd = BDD.build_from_truth_table(truth_table)
        self.assertEqual(bdd.num_beads, 7)
        self.assertEqual(bdd.num_solutions, 8)
    
    def test_invalid_truth_table_length(self):
        with self.assertRaises(ValueError):
            BDD.build_from_truth_table("101")

    def test_display_function(self):
        truth_table = "1100100100001111"
        bdd = BDD.build_from_truth_table(truth_table)
        print("Example of tree visualization:")
        bdd.display()  # This will print the tree structure; visually inspect it