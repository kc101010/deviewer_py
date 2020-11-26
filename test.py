import deviewer

print(deviewer.get_os())

#print memory in GB
memory = deviewer.get_mem()
memory = memory // 1024 // 1024

print(memory + 1)

print(deviewer.get_gpu())
print(deviewer.get_cpu())
print(deviewer.get_user())
print(deviewer.version())