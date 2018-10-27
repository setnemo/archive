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

    public function performQuery(string $url)
    {
        $q = $this->getQuery($url);
        $ch = curl_init(); 
        curl_setopt($ch, CURLOPT_URL, $q);
        curl_setopt($ch, CURLOPT_USERPWD, $this->token);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        $result = curl_exec($ch);
        curl_close($ch);

        // return json_decode($result);
        return $result;
    }

    public function getQuery($url) {
        $base = 'https://' . $this->urlBase . 'coverage/' . $this->coverage . '/';
        return  $base . $url;
    }
}

$c = new RatpClient();
$r = $c->getPlace('asd');
print_r($r);

