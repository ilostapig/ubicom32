
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_javax_net_ssl_provider_CertificateVerify__
#define __gnu_javax_net_ssl_provider_CertificateVerify__

#pragma interface

#include <gnu/javax/net/ssl/provider/Signature.h>
#include <gcj/array.h>

extern "Java"
{
  namespace gnu
  {
    namespace javax
    {
      namespace net
      {
        namespace ssl
        {
          namespace provider
          {
              class CertificateVerify;
              class SignatureAlgorithm;
          }
        }
      }
    }
  }
  namespace java
  {
    namespace nio
    {
        class ByteBuffer;
    }
  }
}

class gnu::javax::net::ssl::provider::CertificateVerify : public ::gnu::javax::net::ssl::provider::Signature
{

public:
  CertificateVerify(::java::nio::ByteBuffer *, ::gnu::javax::net::ssl::provider::SignatureAlgorithm *);
  CertificateVerify(JArray< jbyte > *, ::gnu::javax::net::ssl::provider::SignatureAlgorithm *);
  virtual ::java::lang::String * toString();
  virtual ::java::lang::String * toString(::java::lang::String *);
  static ::java::lang::Class class$;
};

#endif // __gnu_javax_net_ssl_provider_CertificateVerify__
