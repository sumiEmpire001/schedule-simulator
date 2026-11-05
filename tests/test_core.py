import unittest
from schedule_simulator import simulate

class Tests(unittest.TestCase):
    def test_fcfs(self):
        r = simulate([{"id":"a","arrival":0,"burst":4},{"id":"b","arrival":1,"burst":2}])
        self.assertEqual([x["id"] for x in r["timeline"]], ["a","b"])
        self.assertEqual(r["metrics"]["b"]["waiting"], 3)
    def test_sjf(self):
        jobs = [{"id":"a","arrival":0,"burst":5},{"id":"b","arrival":0,"burst":1}]
        self.assertEqual(simulate(jobs,"sjf")["timeline"][0]["id"], "b")
    def test_rr(self):
        jobs = [{"id":"a","arrival":0,"burst":3},{"id":"b","arrival":0,"burst":2}]
        r = simulate(jobs,"rr",quantum=1)
        self.assertEqual([x["id"] for x in r["timeline"]], ["a","b","a","b","a"])
        self.assertEqual(r["metrics"]["a"]["completion"], 5)
    def test_idle_and_invalid(self):
        self.assertEqual(simulate([])["timeline"], [])
        self.assertEqual(simulate([{"id":"x","arrival":5,"burst":1}])["timeline"][0]["start"], 5)
        with self.assertRaises(ValueError):
            simulate([{"id":"x","arrival":0,"burst":0}])
        with self.assertRaises(ValueError):
            simulate([], "unknown")
