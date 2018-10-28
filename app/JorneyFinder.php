<?php

class JourneyFinder {

    public function bfs(array $root, $first, $goal)
    {
        $open = new SplQueue();
        $closed = new SplQueue();

        $open->enqueue('none@' . $first);
        $way = [];
        while (!$open->isEmpty()) {
            $now = $open->dequeue();
            $now = $root[substr(strstr($now, '@'), 1)];
            if ($now['name'] === $goal['name']) {
                return array_unique($way);
            }
            // return substr(strstr($now, '@'), 1);
            foreach ($now['links'] as $value) {
                if (in_array($now['name'] . '@' . $value['next'], iterator_to_array($closed))) {
                    continue;
                }
                if (!in_array($now['name'] . '@' . $value['next'], iterator_to_array($open))) {
                    $way[] = $now['name'] . '@' . $value['next'];
                    $open->enqueue($now['name'] . '@' . $value['next']);
                }
            }
            $closed->enqueue($now['name']);
        }
    }

    public function getJourney(array $routes, string $first, string $last)
    {
        $stop = 0;
        $matrix = $this->getMatrix($routes);
        $map = $this->getMap2($routes);
        $journey1 = array();
        $queue = array();
        // foreach ($map[$first] as &$key) {
        //     $key['dist'] = 0;
        // }
        // $iterat = $this->lastNotFound($queue, $last, $map);
        // $queue = $map[$first];
        $test = $this->bfs($map, $first, $map[$last]);
        $go_to = [];
        foreach ($test as $value) {
            if (substr(strstr($value, '@'), 1) == $last) {
                $start = $value;
            }
        }
        while (true) {
            echo $start."<br>";
            $go_to[] = $start;
            $start = substr($start, 0, strpos($start, '@'));
            if ($start == 'none') {
                break;
            }
            foreach ($test as $value) {
                if (substr(strstr($value, '@'), 1) == $start) {
                    $start = $value;
                }
            }
        }
        $iterator = 1;
        $new = array();
        return $go_to;
        // return $map;
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

    private function getMap2(array $routes) {
        $matrix = array();
        foreach ($routes as $routename => $route) {
            foreach ($route as $key) {
                if ($this->get_next_station($key['label'], $routename, $routes) !== 'null') {
                $matrix[$key['label']] = 
                array( 'name' => $key['label'],
                );
                }
            }
        }
        foreach ($routes as $routename => $route) {
            foreach ($route as $key) {
                if ($this->get_next_station($key['label'], $routename, $routes) !== 'null') {
                $matrix[$key['label']]['links'][] = array('routename' => $routename, 'next' => $this->get_next_station($key['label'], $routename, $routes), 'dist' => -42);
                }
            }
        }
        return $matrix;
    }
    private function getMap(array $routes) {
        $matrix = array();
        foreach ($routes as $routename => $route) {
            foreach ($route as $key) {
                if ($this->get_next_station($key['label'], $routename, $routes) !== 'null') {
                $matrix[$key['label']][$routename] = array('next' => $this->get_next_station($key['label'], $routename, $routes), 'dist' => -42);
                }
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