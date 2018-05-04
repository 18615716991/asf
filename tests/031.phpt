--TEST--
Check for Asf_Ensure, get started No.3 for build
--SKIPIF--
<?php if (!extension_loaded("asf")) print "skip"; ?>
--INI--
asf.use_namespace=0
--FILE--
<?php
class Constants
{
    const ERR_TEST_CODE = 500;
    const ERR_USER_CODE = 501;
    const ERR_USER_STR  = 'aaa';

    public static $ErrDescription = array(
        self::ERR_TEST_CODE => 'This is test default text',
        self::ERR_USER_CODE => 'This is test user text',
        self::ERR_USER_STR  => 'This is test string',
    );
}

try {
    Asf_Ensure::notNull(null, Constants::ERR_USER_STR);
} catch (Error $e) {
    var_dump($e->getMessage());
}
?>
--EXPECTF--
%s

