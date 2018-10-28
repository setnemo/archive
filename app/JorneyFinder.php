<?php

class JourneyFinder {

    public function getJourney(array $routes, string $first, string $last)
    {
        $stop = 0;
        $matrix = $this->getMatrix($routes);
        $map = $this->getMap($routes);
        $journey1 = array();
        $queue = array();
        $queue = $map[$first];
        foreach ($map[$first] as &$key) {
            $key['dist'] = 0;
        }
        $iterat = $this->lastNotFound($queue, $last, $map);
        // while ($iterat)
        // {

        // }
        return $queue;
    }

    private function getMatrix(array $routes) {
        $matrix = array();
        foreach ($routes as $routename => $route) {
            foreach ($route as $key) {
                $matrix[$key['label']][] = $routename;
            }
        }
        return $matrix;
    }

    private function lastNotFound(array $queue, string $last, array &$map)
    {
        foreach ($queue as $key => $line) {
            $map[$line['next']][$key]['dist'] = 1;
            if ($line['next'] === $last)
                return false;
        }
        return true;
    } 

    private function getMap(array $routes) {
        $matrix = array();
        foreach ($routes as $routename => $route) {
            foreach ($route as $key) {
                $matrix[$key['label']][$routename] = array('next' => $this->get_next_station($key['label'], $routename, $routes), 'dist' => -42);
            }
        }
        return $matrix;
    }

    private function get_next_station(string $label, string $line, array $routes) {
        $stop = 0;
        foreach ($routes[$line] as $station) {
            if ($stop == 0 && $station['label'] !== $label) {
                continue ;
            }
            $stop++;
            if ($stop == 2) {
                return $station['label'];
            }

        }
        return 'null';
    }
}