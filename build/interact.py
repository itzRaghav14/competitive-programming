#!/usr/bin/env python3

import argparse
import subprocess as sp
import threading
from queue import Queue, Empty
import sys
import time


def intercept(out, q):
	for line in iter(out.readline, b''):
		q.put(line)
	out.close()


class ProcessThread:
	def __init__(self, cmd):
		self.p = sp.Popen(cmd, stdin=sp.PIPE, stdout=sp.PIPE, stderr=sp.PIPE, close_fds=("posix" in sys.builtin_module_names))
		self.q = dict()
		self.listen = dict()
		for stream, name in zip([self.p.stdout, self.p.stderr], ["out", "err"]):
			self.q[name] = Queue()
			self.listen[name] = threading.Thread(target=intercept, args=(stream, self.q[name]))
			self.listen[name].daemon = True
			self.listen[name].start()


	def feed_input(self, inp):
		if self.poll() is not None:
			return
		self.p.stdin.write((inp + "\n").encode())
		self.p.stdin.flush()


	def get_stream(self, stream):
		if self.poll() is not None:
			return None
		lines = []
		while True:
			try:
				line = self.q[stream].get_nowait()
				lines.append(line)
			except Empty:
				break
		return None if lines == [] else "\n".join(map(lambda x: x.decode().strip(), lines))

	def get_out(self):
		return self.get_stream("out")

	def get_err(self):
		return self.get_stream("err")

	def poll(self):
		return self.p.poll()


color_codes = {
	"Reset": 0,
	"Bold": 1,
	"Underline": 2,
	"Inverse": 7,
	"Black": 30,
	"Red": 31,
	"Green": 32,
	"Yellow": 33,
	"Blue": 34,
	"Magenta": 35,
	"Cyan": 36,
	"White": 37,
}

def colored(text, color):
	if color not in color_codes:
		return text
	return f"\033[{color_codes[color]}m{text}\033[0m"


def print_framed(text, left_appendix="", right_appendix="", color="normal"):
	pass
	# print(colored(text, color.capitalize()))
	# color = color.capitalize()
	# lines = text.strip().split('\n')
	# width = max(map(len, lines)) + 2
	# print(colored(" " * len(left_appendix) + "+" + "-" * width + "+", color))
	# for line in lines:
	# 	print(colored(" " * len(left_appendix) + "| ", color) + line.ljust(width - 2, ' ') + colored(" |", color))
	# print(colored(left_appendix + "+" + "-" * width + "+" + right_appendix, color))


parser = argparse.ArgumentParser(description="Make two programs interact with each other.")
parser.add_argument("solution", metavar="<solution exec>", help="Executable file of the solution to test")
parser.add_argument("interactor", metavar="<interactor exec>", help="Executable file of the interactor to test your solution against.")
parser.add_argument("-c", "--color", action="store_true", help="Colored frames")
parser.add_argument("--no-stderr", action="store_true", help="Disable stderr printing")
parser.add_argument("--hang-timeout", type=float, default=1, help="The number of seconds to wait for the solution to exit after the interactor has finished")

args = parser.parse_args()

solution = ProcessThread(args.solution)
interactor = ProcessThread(args.interactor)
testcases = 10000
HANG_TIMEOUT = args.hang_timeout


class Tester:
	def run(self):
		self.solution = ProcessThread(args.solution)
		self.interactor = ProcessThread(args.interactor)
		self.solution_running = True
		self.interactor_running = True
		self.hanging_start = None
		self.interactions = []
		self.verdict = "OK"

		while True:
			if self.solution_running and self.solution.poll() is not None:
				solution_exit_code = self.solution.poll()
				self.add_interaction(f"Solution process exited with error code {solution_exit_code}", "red" if solution_exit_code else "green")
				self.solution_running = False
				if solution_exit_code: self.verdict = "RE"

			if self.interactor_running and self.interactor.poll() is not None:
				interactor_exit_code = self.interactor.poll()
				self.add_interaction(f"Iterator process exited with error code {interactor_exit_code}", "red" if interactor_exit_code else "green")
				self.interactor_running = False
				if interactor_exit_code: self.verdict = "WA"

			if not self.solution_running and not self.interactor_running:
				if self.verdict == "OK": self.interactions = []
				self.add_interaction(f"Verdict: {self.verdict}", "red" if self.verdict != "OK" else "green")
				self.print_interaction()
				if self.verdict == "OK": break
				sys.exit(0)

			if self.solution_running and not self.interactor_running:
				if self.hanging_start is None:
					self.hanging_start = time.time()
				if time.time() - self.hanging_start >= HANG_TIMEOUT:
					self.verdict = "TLE"
					self.add_interaction(f"Solution process has been forced to shut down due to timeout", "red")
					sys.exit(0)

			soln_out = self.solution.get_out()
			inter_out = self.interactor.get_out()
			soln_err = self.solution.get_err()
			inter_err = self.interactor.get_err()

			if soln_out is not None:
				self.add_interaction(soln_out, "yellow")
				print_framed(soln_out, "solution: ", "", "green" if args.color else "")
				self.interactor.feed_input(soln_out)
				self.hanging_start = None
			if soln_err is not None and not args.no_stderr:
				print_framed(soln_err, "  stderr: ", "", "magenta" if args.color else "")
				self.hanging_start = None
			if inter_out is not None:
				self.add_interaction(inter_out, "cyan")
				print_framed(inter_out, "          ", " :interactor", "cyan" if args.color else "")
				self.solution.feed_input(inter_out)
			if inter_err is not None and not args.no_stderr:
				self.add_interaction(inter_err, "blue")
				print_framed(inter_err, "          ", " :interactor stderr", "red" if args.color else "")
		
	def add_interaction(self, text, color):
		self.interactions.append([text, color.capitalize()])
	
	def print_interaction(self):
		for text, color in self.interactions:
			print(colored(text, color))


tester = Tester()

for i in range(1, testcases + 1):
	print("Running test case", i)
	tester.run()
	print()