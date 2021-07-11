def cdlib_get_value(data, low_mul, high_mul):
    data_len = len(data)
    if( (data_len > high_mul) or (data_len < low_mul) ):
        raise Exception("assert error")
    # Now only get the first value
    return data[0]['Value']
