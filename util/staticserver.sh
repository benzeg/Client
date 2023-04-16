#!/usr/bin/env python3
from http.server import HTTPServer, SimpleHTTPRequestHandler
import ssl

class CORSRequestHandler(SimpleHTTPRequestHandler):
	def end_headers(self):
		self.send_header('Cross-Origin-Opener-Policy', 'same-origin')
		self.send_header('Cross-Origin-Embedder-Policy', 'require-corp')
		self.send_header('Access-Control-Allow-Origin', '*')
		return super(CORSRequestHandler, self).end_headers()


httpd = HTTPServer(('0.0.0.0', 443), CORSRequestHandler)
context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
context.load_cert_chain(certfile='cert.pem', keyfile='key.pem', password='password')

httpd.socket = context.wrap_socket(httpd.socket)

httpd.serve_forever()
