"""Thin wrapper around the PowerPC GNU binutils (as, ld, objdump).

On Windows the cross binutils usually live inside WSL. When the tools are not
on PATH but `wsl` is, they are run through `wsl -e` and host paths are
translated to /mnt/<drive>/... paths.

Environment overrides:
	T6P_CROSS_PREFIX  tool prefix (default "powerpc-linux-gnu-")
	T6P_WRAPPER       command prefix, e.g. "wsl -e", or "" to run tools directly
"""

import os, shlex, shutil, subprocess

class ToolError(Exception):
	pass

class Toolchain:
	def __init__(self, prefix=None, wrapper=None):
		self.prefix = prefix or os.environ.get("T6P_CROSS_PREFIX", "powerpc-linux-gnu-")
		if(wrapper is None): wrapper = os.environ.get("T6P_WRAPPER")
		if(wrapper is None):
			if(shutil.which(self.prefix + "as")): wrapper = ""
			elif(os.name == "nt" and shutil.which("wsl")): wrapper = "wsl -e"
			else:
				raise ToolError(
					f"{self.prefix}as not found. Install binutils-powerpc-linux-gnu "
					"(or set T6P_CROSS_PREFIX / T6P_WRAPPER).")
		self.wrapper = shlex.split(wrapper)
		self.wsl = bool(self.wrapper) and \
			os.path.basename(self.wrapper[0]).lower().startswith("wsl")

	# Translate a host path into a path the tools understand.
	def path(self, p):
		p = os.path.abspath(p)
		if(self.wsl):
			drive, rest = os.path.splitdrive(p)
			if(drive): return "/mnt/" + drive[0].lower() + rest.replace("\\", "/")
		return p

	def run(self, tool, args, cwd=None):
		cmd = self.wrapper + [self.prefix + tool] + [str(a) for a in args]
		r = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True)
		if(r.returncode != 0):
			raise ToolError("{:s} failed:\n  {:s}\n{:s}{:s}".format(
				tool, " ".join(cmd), r.stdout, r.stderr))
		return r.stdout

	def assemble(self, src, obj, flags=(), includes=()):
		args = ["-a32", "-be"] + list(flags)
		for inc in includes: args += ["-I", self.path(inc)]
		args += ["-o", self.path(obj), self.path(src)]
		self.run("as", args)

	# The linker script INCLUDEs files relative to `cwd`. Orphan sections are
	# not an ld error (ld always makes empty .glink/.iplt/...); the caller
	# rejects any unexpected non-empty section in the output instead.
	def link(self, script, objs, out, cwd):
		args = ["-e", "0", "-L", self.path(cwd),
			"-T", self.path(script), "-o", self.path(out)]
		self.run("ld", args + [self.path(o) for o in objs], cwd=cwd)

	def disassemble(self, elf):
		return self.run("objdump", ["-d", "-z", self.path(elf)])
