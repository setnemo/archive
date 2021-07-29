<?php

include_once ROOT.'/models/Token.php';

class TokenController {
  
  public function actionIndex() {

      return true;
  }

  public function actionExternal($token, $email) {

    $status = Token::confirmToken($token, $email);
    require_once(ROOT.'/views/login/token-confirm.php');
    return true;
  }

  public function action404() {
      require_once(ROOT.'/views/login/index.php');
      return true;
  }
}