def read_file_strings(input_filename: str):
    lines = []
    with open("i", 'r') as f:
        lines = f.read().splitlines()

    return lines


def parse_times_distances():
    info = read_file_strings("i")
    time_str = info[0].split(":")[1]
    times = [int(x) for x in time_str.split(' ') if x.isdigit()]

    dist_str = info[1].split(":")[1]
    dists = [int(x) for x in dist_str.split(' ') if x.isdigit()]

    return times, dists


def parse_single_time_distance():
    info = read_file_strings("i")
    time_str = info[0].split(":")[1]
    time = ''.join([x for x in time_str.split(' ') if x.isdigit()])

    dist_str = info[1].split(":")[1]
    dist = ''.join([x for x in dist_str.split(' ') if x.isdigit()])

    return int(time), int(dist)


def part1():
    times, dists = parse_times_distances()

    product_num_ways = 1
    for i in range(len(times)):
        t, d = times[i], dists[i]

        num_ways_to_win = 0
        for hold_time in range(d):
            travel_time = t - hold_time
            dist_traveled = hold_time * travel_time

            if dist_traveled > d:
                # went further than record
                num_ways_to_win += 1

        product_num_ways *= num_ways_to_win

    return product_num_ways


def part2():
    time, dist = parse_single_time_distance()

    earliest_win_hold_time = 0
    for hold_time in range(dist):
        travel_time = time - hold_time
        dist_traveled = hold_time * travel_time

        if dist_traveled > dist:
            # went further than record
            earliest_win_hold_time = hold_time
            break

    latest_win_hold_time = time - earliest_win_hold_time

    num_ways_to_win = latest_win_hold_time - earliest_win_hold_time + 1
    return num_ways_to_win


# print(f"Part 1: {part1()}")
print(f"Part 2: {part2()}")
