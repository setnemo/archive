<?php

class RatpClient {

    private $urlBase = 'api.navitia.io/v1/';

    private $coverage = 'fr-idf';

    private $token = 'fd1abb9a-aef3-421c-8da4-e1a78c490af9:';

    public function getPlace(string $userInput) {
        $q = 'places?q=' . $userInput . '&type[]=address';
        return $this->performQuery($q);
    }

    public function getCoords(string $place) {
        // $q = 
    }

    public function performQuery(string $url) {
        $ch = curl_init(); 
        curl_setopt($ch, CURLOPT_URL, $this->getQuery($url));
        curl_setopt($ch, CURLOPT_USERPWD, $this->token);
        $result = curl_exec($ch);
        curl_close($ch);

        return json_decode($result);
    }

    public function getQuery($url) {
        return 'https://' . $this->urlBase . 'coverage/' . $this->coverage . '/' . $url;
    }
}

$c = new RatpClient();

var_dump($c->getPlace('asb'));
