import hashlib

def func(var):
	res = hashlib.sha512(var.encode('utf-8'))
	res = res.hexdigest()
	return res
k = '9899999999'
for i in range(10):
	k = func(k)
	k = k
	print(k,i)