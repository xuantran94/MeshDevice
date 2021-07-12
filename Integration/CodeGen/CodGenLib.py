def cdlib_get_value(data, low_mul, high_mul):
    data_len = len(data)
    if( (data_len > high_mul) or (data_len < low_mul) ):
        raise Exception("assert error")
    # Now only get the first value
    return data[0]['Value']

def cdlib_push(dict1, dict2):
    for k in set(dict1.keys()).union(dict2.keys()):
        if k in dict1 and k in dict2:
            if isinstance(dict1[k], dict) and isinstance(dict2[k], dict):
                yield (k, dict(cdlib_push(dict1[k], dict2[k])))
            else:
                # If one of the values is not a dict, you can't continue merging it.
                # Value from second dict overrides one in first and we move on.
                yield (k, dict2[k])
                # Alternatively, replace this with exception raiser to alert you of value conflicts
        elif k in dict1:
            yield (k, dict1[k])
        else:
            yield (k, dict2[k])
