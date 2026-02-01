"""ESPHome custom component for PT2262 remote control transmission."""
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins, automation
from esphome.const import CONF_ID, CONF_PIN, CONF_REPEAT

CODEOWNERS = ["@rmrfslashbin"]
DEPENDENCIES = []

pt2262_ns = cg.esphome_ns.namespace("pt2262")
PT2262Component = pt2262_ns.class_("PT2262Component", cg.Component)
PT2262SendAction = pt2262_ns.class_("PT2262SendAction", automation.Action)

CONF_CODE = "code"
CONF_PT2262_ID = "pt2262_id"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(PT2262Component),
        cv.Required(CONF_PIN): pins.internal_gpio_output_pin_schema,
        cv.Optional(CONF_REPEAT, default=4): cv.int_range(min=1, max=20),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    """Generate C++ code for the PT2262 component."""
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    pin = await cg.gpio_pin_expression(config[CONF_PIN])
    cg.add(var.set_pin(pin))

    cg.add(var.set_repeat_times(config[CONF_REPEAT]))


# Action for sending PT2262 codes
@automation.register_action(
    "pt2262.send",
    PT2262SendAction,
    cv.Schema(
        {
            cv.GenerateID(): cv.use_id(PT2262Component),
            cv.Required(CONF_CODE): cv.templatable(cv.string),
        }
    ),
)
async def pt2262_send_to_code(config, action_id, template_arg, args):
    """Generate code for pt2262.send action."""
    paren = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, paren)

    template_ = await cg.templatable(config[CONF_CODE], args, cg.std_string)
    cg.add(var.set_code(template_))

    return var
