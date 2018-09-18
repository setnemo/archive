#!/bin/bash
set -euo pipefail

cat >> /etc/msmtprc <<-EOCFG
account         default
host         smtp.sendgrid.net
port         587
timeout         30
auth         on
tls          on
tls_starttls    on
tls_trust_file     /etc/ssl/certs/ca-certificates.crt
syslog          on

auto_from       off
user         ${MTA_SENDGRID_USER}
password        ${MTA_SENDGRID_PASS}
from         ${MTA_SENDGRID_FROM}
maildomain      ${MTA_SENDGRID_MAILDOMAIN}
EOCFG


exec "$@"