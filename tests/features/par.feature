Feature: par

    Scenario: Invoke par
        When I run the command: par --help
        Then I see the line in standard output: List image formats

    Scenario: Print all parameters
        Given I am in the heimdali data directory
        When I run the command: par imtest_z5_y4_x3_c2.<ext>
        Then I see the standard output:
            """
            imtest_z5_y4_x3_c2.<ext> -x 3	-y 4	-z 5	-v 2	-o 4
            ""
            """
    Examples:
      | ext |
      | h5  |
      | inr |

    Scenario: Print one parameter
        Given I am in the heimdali data directory
        When I run the command: par imtest_z5_y4_x3_c2.h5 -x
        Then I see the standard output:
            """
            " -x 3"
            """

    Scenario: Print file type
        Given I am in the heimdali data directory
        When I run the command: par imtest_z5_y4_x3_c2.<ext> -F
        Then I see the standard output:
            """
            " -F <filetype>"
            """
    Examples:
      | ext | filetype |
      | h5  | HDF5     |
      | inr | Inrimage |

    Scenario: Print parameters of image with origin different than 0
        Given I am in the heimdali data directory
        When I run the command: par imtest_z5_y4_x3_c2_origin_4_5_6.<ext>
        Then I see the standard output:
            """
            imtest_z5_y4_x3_c2_origin_4_5_6.<ext> -x 3	-y 4	-z 5	-v 2	-x0 4	-y0 5	-z0 6	-o 4
            ""
            """
    Examples:
      | ext |
      | h5  |
      | inr |

    Scenario: Print parameters of image with one plane and one pixel component
        Given I am in the heimdali data directory
        When I run the command: par imtest_z1_y3_x2_c1.<ext>
        Then I see the standard output:
            """
            imtest_z1_y3_x2_c1.<ext> -x 2	-y 3	-o 4
            ""
            """
    Examples:
      | ext |
      | h5  |
      | inr |
